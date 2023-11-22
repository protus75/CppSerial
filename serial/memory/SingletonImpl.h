#ifndef SERIAL_MEMORY_SINGLETON_IMPL_H
#define SERIAL_MEMORY_SINGLETON_IMPL_H

#include "Singleton.h"

namespace serial::memory
{
	template <typename T> Singleton<T>*& SingletonImpl<T>::rpData()
	{
		static Singleton<T>* spData(0);
		return spData;
	}

	template <typename T> void SingletonImpl<T>::InstancePost()
	{
	}

	template <typename T> void SingletonImpl<T>::InstanceImpl()
	{
		rpData() = new Singleton<T>();

		InstancePost();
	}

	template <typename T> void SingletonImpl<T>::DeletePre()
	{
	}

	template <typename T> bool SingletonImpl<T>::Is()
	{
		return (0 != rpData());
	}

	template <typename T> void SingletonImpl<T>::Delete()
	{
		if (Is())
		{
			DeletePre();
		}

		delete rpData();
		rpData() = 0;
	}
}

namespace serial::memory
{
	template <typename T> T& Instance()
	{
		return SingletonImpl<T>::Instance();
	}

	template <typename T> void Delete()
	{
		SingletonImpl<T>::Delete();
	}
}

#endif