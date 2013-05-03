class PostsController < ApplicationController
  before_filter :authenticate_user!, :except => [:index, :show]
  inherit_resources
end
