#ifndef SERIAL_MEMORY_SINGLETON_IMPL_H
#define SERIAL_MEMORY_SINGLETON_IMPL_H

#include "Singleton.h"

namespace serial::memory
{
	template <typename T> Singleton<T>*& SingletonImpl<T>::_pData()
	{
		static Singleton<T>* spData(0);
		return spData;
	}

	template <typename T> void SingletonImpl<T>::InstancePost()
	{
	}

	template <typename T> void SingletonImpl<T>::_InstanceImpl()
	{
		_pData() = new Singleton<T>();

		InstancePost();
	}

	template <typename T> void SingletonImpl<T>::DeletePre()
	{
	}

	template <typename T> bool SingletonImpl<T>::_IsExist()
	{
		return (0 != _pData());
	}

	template <typename T> void SingletonImpl<T>::_Delete()
	{
		if (_IsExist())
		{
			DeletePre();
		}

		delete _pData();
		_pData() = 0;
	}

	template <typename T> T& SingletonImpl<T>::_Instance()
	{
		if (!_IsExist())
		{
			_InstanceImpl();
		}

		return _pData()->mSingleton;
	}
}

namespace serial::memory
{
	template <typename T> T& Instance()
	{
		return SingletonImpl<T>::_Instance();
	}

	template <typename T> bool IsExist()
	{
		return SingletonImpl<T>::_IsExist();
	}

	template <typename T> void Delete()
	{
		SingletonImpl<T>::_Delete();
	}
}

#endif