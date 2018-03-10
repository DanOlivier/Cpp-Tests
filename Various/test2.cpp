#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <vector>
#include <set>

#include <boost/filesystem.hpp>

struct Result {
    boost::filesystem::path root;
	std::vector<boost::filesystem::path> files;
	std::vector<boost::filesystem::path> dirs;
	Result(const boost::filesystem::path& r) :root(r) {}
	Result(const Result&& r) : root(r.root), files(std::move(r.files)), dirs(std::move(r.dirs)) {}
};

Result listDir(boost::filesystem::path&& dir)
{
	Result result(dir);
	for(boost::filesystem::directory_iterator it(dir); 
		it != boost::filesystem::directory_iterator(); ++it)
	{
		if(boost::filesystem::is_directory(it->status()))
			result.dirs.push_back(it->path());
		else
			result.files.push_back(it->path().leaf());
	}
	return result;
}

int main()
{
	std::string root = "/home/daniel/tools";
    std::vector<boost::filesystem::path> dirsToDo;
    std::set<boost::filesystem::path> dirsDone;
	dirsToDo.push_back(root);

	std::vector<boost::filesystem::path> files;
	while(!dirsToDo.empty())
	{
		std::vector<std::future<Result>> futures;
		for(int i = 0; i < 16 && !dirsToDo.empty(); ++i)
		{
			auto fut = std::async(&listDir, std::move(dirsToDo.back()));
			dirsToDo.pop_back();
			futures.push_back(std::move(fut));
		}

		try
		{
			while(!futures.empty())
			{
				auto ftr = std::move(futures.back());
				futures.pop_back();
				Result result = ftr.get();
                dirsDone.insert(result.root);
				//std::copy(result.files.begin(), result.files.end(), std::back_inserter(files));
                for(auto f: result.files)
                {
                    files.push_back(boost::filesystem::canonical(f, result.root));
                }
				//std::copy(result.dirs.begin(), result.dirs.end(), std::back_inserter(dirsToDo));
                for(auto d: result.dirs)
                {
                	if(boost::filesystem::is_symlink(d))
                        //d = boost::filesystem::read_symlink(d);
                        d = boost::filesystem::canonical(d, result.root);
                    if(dirsDone.find(d) == dirsDone.end())
                        dirsToDo.push_back(d);
                    else {
                        std::cout << d << " already passed" << std::endl;
                    }
                }
			}
		}
		catch(std::system_error& e)
		{
			std::cout << "System error: " << e.code().message() << std::endl;
		}
		catch(std::exception& e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
		catch(...)
		{
			std::cout << "Unknown exception" << std::endl;
		}
	}

	std::for_each(files.begin(), files.end(), [](boost::filesystem::path& p)
	{
		std::cout << p << "\n";
	});

	std::cout << "\nPress enter\n";
	char c;
	std::cin.get(c);
}
