#ifndef _TEST_RESOURCE_MANAGER_H_
#define _TEST_RESOURCE_MANAGER_H_

#include <stdexcept>  // ��׼�쳣��
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
        {  // �����׼�쳣
            std::cerr << "Error: " << e.what() << std::endl;  // ����쳣��Ϣ
        }
        catch(const std::string& msg)
        {
            std::cerr << msg << std::endl;
        }
        catch (const char* msg)
        {  // ���� ANSI �ַ���
            std::cerr << "Error: " << msg << std::endl;
        }
        catch (const wchar_t* msg)
        {  // ���� Unicode �ַ���
            std::wcerr << L"Error: " << msg << std::endl;
        }
        catch (...)
        {  // �������������쳣�����Ƽ�����ʹ�ã�
            std::cerr << "An unknown error occurred." << std::endl;
        }
        
        std::cout << "ResourceManager instance is fine!." << std::endl;
        rm->show_resource_info_size();
	}
};


#endif // !_TEST_RESOURCE_MANAGER_H_