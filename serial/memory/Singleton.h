#ifndef SERIAL_MEMORY_SINGLETON_H
#define SERIAL_MEMORY_SINGLETON_H

#include "SingletonFwd.h"

namespace serial::memory
{
template <typename T>
class Singleton
{
	friend class SingletonImpl<T>;

	T mSingleton;
};

template <typename T> T& Instance();

template <typename T> void Delete();

}

namespace serial::memory
{
template <typename T>
class SingletonImpl
{
	friend T& Instance<T>();

	friend void Delete<T>();

public:

	static void InstancePost();

	static void DeletePre();

	static bool Is();

private:

	SingletonImpl() = default;

	SingletonImpl(const SingletonImpl<T>& aCopy) = delete;

	SingletonImpl<T> operator=(const SingletonImpl<T>& aCopy) = delete;

	static T& Instance();

	static void InstanceImpl();

	static Singleton<T>*& rpData();

	static void Delete();
};
}

#endif