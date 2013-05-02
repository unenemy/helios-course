#usage: $ thin start -R async_app.ru -p 4242
#       $ ab -n 1000 -c 100 http://localhost:4242/
require 'mysql2'
require 'mysql2/em'

# pool for async sql queries
class MysqlConnectionPool
  def initialize(conf)
    @pool_size = conf[:size] || 10
    @connections = []
    @query_queue = EM::Queue.new
    start_queue conf
  end

  def queue_worker_loop
    proc{ |connection|
      @query_queue.pop do |query|
        sql = query[:sql].is_a?(Proc) ? query[:sql].call(connection) : query[:sql]

        connection.query(sql, query[:opts]).callback do |result|
          query[:callback].call result if query[:callback]
          queue_worker_loop.call connection
        end
      end
    }
  end

  def start_queue(conf)
    @pool_size.times do
      connection = Mysql2::EM::Client.new(conf)
      @connections << connection
      queue_worker_loop.call connection
    end
  end

  def query(sql, opts={}, &block)
    @query_queue.push :sql => sql, :opts => opts, :callback => block
  end
end

class DeferrableBody
  include EventMachine::Deferrable

  def call(body)
    body.each do |chunk|
      @body_callback.call(chunk)
    end
  end

  def each &blk
    @body_callback = blk
  end

end

class AsyncApp

  AsyncResponse = [-1, {}, []].freeze
  def sql_pool
    @sql_pool ||= MysqlConnectionPool.new(:host => "localhost", :user => "root")
  end

  def call(env)

    body = DeferrableBody.new

    EventMachine::next_tick { env['async.callback'].call [200, {'Content-Type' => 'text/plain'}, body] }
    EventMachine::next_tick {
      # we dont wait the query finish but push it to the queue
      sql_pool.query "select sleep(0.1)" do
        puts "okay"
      end
      body.call ["Hello world"]
      body.succeed
    }

    AsyncResponse
  end

end

run AsyncApp.new
