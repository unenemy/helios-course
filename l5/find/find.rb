require 'optparse'
require 'etc'
OPTIONS = %w[name cnewer type user maxdepth]
OPTIONS_EXPLANATIONS = {
  "name" => "Search pattern",
  "cnewer" => "Find all newer then specified file",
  "type" => "Filetype - (d - directory, s - socket, f - file, l - symlink, e - everything)",
  "user" => "Owner of file",
  "maxdepth" => "Directory search depth"
}

FILECHECK = {
  "d" => "directory?",
  "s" => "socket?",
  "l" => "symlink?",
  "f" => "file?",
  "e" => "exists?"
}

def parse_options
  options = {}
  OptionParser.new do |opts|
    opts.banner = "Usage: find.rb dirpath [options]"

    OPTIONS.each do |option|
      opts.on("--#{option} #{option.upcase}", String, "#{OPTIONS_EXPLANATIONS[option]}"){|v| options[option.to_sym] = v  }
    end
  end.parse!
  options[:dir] = ARGV.first
  options
end

def go_deeper?(depth, maxdepth)
  maxdepth == 0 || depth < maxdepth
end

def searchable_dir?(filename, fullname)
  File.directory?(fullname) && ![".", ".."].include?(filename)
end

def file_matches_needs?(filename, fullname, regexp, typecheck, user, cnewer)
  file_owner = Etc.getpwuid(File.stat(fullname).uid).name
  filename.match(regexp) &&
    File.send(typecheck, fullname) &&
    (!user || user == file_owner) &&
    (!cnewer || File.mtime(cnewer) < File.mtime(fullname))
end

def print_results(files)
  message = "In directory #{@options[:dir]} searching for #{@options[:name]}"
  @options.select{|k,v| ![:dir, :name].include?(k)}.each do |k,v|
    message += " where #{k} = #{v}"
  end
  message += " found:"
  puts message
  puts files
end

def find
  @options = parse_options
  dir            = @options[:dir]
  regexp         = @options[:name] || ""
  user           = @options[:user]
  maxdepth       = @options[:maxdepth].to_i || 0
  cnewer         = @options[:cnewer]
  filetype_check = FILECHECK[@options[:type]] || FILECHECK["e"]
  if !dir
    puts "Directory is not specified! See --help."
    return
  else
    if Dir.exists?(dir)
      matched_files = []
      add_all_from_dir = ->(dir_str, depth){
        Dir.foreach(dir_str) do |filename|
          fullname = [dir_str, filename].join('/')
          matched_files << fullname if file_matches_needs?(filename, fullname, regexp, filetype_check, user, cnewer)
          add_all_from_dir[fullname, depth + 1] if searchable_dir?(filename, fullname) && go_deeper?(depth, maxdepth)
        end
      }
      add_all_from_dir[dir, 1]
      print_results(matched_files)
    else
      puts "Directory #{dir} doesn't exists!"
      return
    end
  end
end

find
