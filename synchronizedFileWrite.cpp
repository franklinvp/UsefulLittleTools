#include <iostream>
#include <mutex>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <thread>
#include <vector>

class SynchronizedFile {
public:
    static SynchronizedFile& getInstance() 
    {
        static SynchronizedFile instance;
        return instance;
    }

private:
    std::ostringstream i_buf;
    std::ofstream i_fout;
    std::mutex _writerMutex;

    SynchronizedFile () {
        i_fout.open("LOGFILE.txt", std::ofstream::out);
        i_buf.precision(17);
        i_buf.setf(std::ios::scientific, std::ios::floatfield);
    }

public:
    SynchronizedFile(SynchronizedFile const&) = delete;
    void operator=(SynchronizedFile const&)   = delete;

    template<typename... Args>
    void write(Args&&... args)
    {
        std::unique_lock<std::mutex> lock(_writerMutex);
        _write(std::forward<Args>(args)...);
    }

private:
    template<typename First, typename... Rest>
    void _write(First param1, Rest...param) 
    {
        i_buf << param1 << ", ";
        _write(param...);
    }

    void _write() 
    {
        i_fout << i_buf.str() << std::endl;
        i_buf.str("");
        i_buf.clear();
    }
};

// Just a class that uses the SynchronizedFile class.
// For testting only.
class Writer {
public:
    Writer (SynchronizedFile& sf, const std::string& prefix) : syncedFile(sf), prefix(prefix) {}

    void someFunctionThatWritesToFile () {
        syncedFile.write(prefix, "AAAAA", 4343, "BBBBB", 0.2345435, "GGGGGG");
    }
private:
    SynchronizedFile& syncedFile;
    std::string prefix;
};

// To test
struct thread_method
{
    std::string i_name;
    thread_method(std::string name) : i_name(name) {};
    void operator()() 
    {
        SynchronizedFile &my_file1 = SynchronizedFile::getInstance();
        Writer writer1(my_file1, i_name);
        for (int i = 0; i < 100; ++ i)
            writer1.someFunctionThatWritesToFile();
    }
};


int main() 
{
  std::vector<thread_method> tms;
  std::vector<std::thread> vthreads;
  for (int i = 0; i < 20; ++i) 
  {
    thread_method tm(std::string("Writer ") + std::to_string(i) + ":");
    tms.push_back(tm);
    vthreads.push_back(std::thread(tms[i]));
  }

  for (auto& th : vthreads)
  {
    th.join();
  }

  std::cout << "Done" << std::endl;
  return 0;
}

