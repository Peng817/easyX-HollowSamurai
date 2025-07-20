#ifndef _TEST_RESOURCE_MANAGER_H_
#define _TEST_RESOURCE_MANAGER_H_

#include <stdexcept>  // 标准异常类
#include <iostream>

#include "../src/util/resource_manager.h"

class TestResourceManager
{
public:
    static void test()
    {
        test1();
    }
private:

	static void test1()
	{
        ResourceManager* rm = nullptr;
        try
        {
            rm = ResourceManager::get_instance();
        }
        catch (const std::exception& e)
        {  // 捕获标准异常
            std::cerr << "Error: " << e.what() << std::endl;  // 输出异常信息
        }
        catch(const std::string& msg)
        {
            std::cerr << msg << std::endl;
        }
        catch (const char* msg)
        {  // 捕获 ANSI 字符串
            std::cerr << "Error: " << msg << std::endl;
        }
        catch (const wchar_t* msg)
        {  // 捕获 Unicode 字符串
            std::wcerr << L"Error: " << msg << std::endl;
        }
        catch (...)
        {  // 捕获所有其他异常（不推荐单独使用）
            std::cerr << "An unknown error occurred." << std::endl;
        }
        
        std::cout << "ResourceManager instance is fine!." << std::endl;
        rm->show_resource_info_size();
	}
};


#endif // !_TEST_RESOURCE_MANAGER_H_