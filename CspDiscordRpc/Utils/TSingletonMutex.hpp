#ifndef TSINGLETON_MUTEX_HPP
#define TSINGLETON_MUTEX_HPP

#include <mutex>
#include <typeindex> // std::type_index

template <typename Derived> // Derived = Derived Class
class TSingletonMutex
{
public:
    static inline Derived* GetInstance()
    {
        // Double check
        if (m_instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_instance == nullptr)
            {
                m_instance = new Derived();
            }
        }
        return m_instance;
    }
protected:
    TSingletonMutex() = default;
    ~TSingletonMutex() = default;
    TSingletonMutex(const TSingletonMutex&) = delete;
    TSingletonMutex& operator=(const TSingletonMutex&) = delete;
    TSingletonMutex(TSingletonMutex&&) = delete;
    TSingletonMutex& operator=(TSingletonMutex&&) = delete;
    TSingletonMutex(const TSingletonMutex&&) = delete;
    TSingletonMutex& operator=(const TSingletonMutex&&) = delete;
protected:
    const char* TAG = std::type_index(typeid(*m_instance)).name();
private:
    static inline std::mutex m_mutex;
    static inline Derived* m_instance;
};

#endif // TSINGLETON_MUTEX_HPP