require './time_service'
use Rack::Logger
use Rack::Auth::Basic, "So private info..." do |user, pass|
  user == "admin" && pass == "heliostech"
end
run TimeService.new
