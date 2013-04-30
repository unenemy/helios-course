load "./fixnum.rb"
class TimeService
  TIME_OFFSETS = {
    "paris" => 2,
    "kiev" => 3,
    "hong-kong" => 8
  }
  def call env
    log = env["rack.logger"]
    city = env["PATH_INFO"].match("^/(.*)").captures.first
    log.info "Requested time for city #{city}"
    offset = TIME_OFFSETS[city] || 0
    [200, {"Content-Type" => "text/html"}, ["#{Time.now.utc + offset.hours}"]]
  end
end
