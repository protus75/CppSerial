#ifndef SERIAL_KEY_VALUEIMPL_H
#define SERIAL_KEY_VALUEIMPL_H

#include <iostream>

#include "Value.h"
#include "../format/FormatImpl.h"
#include "NodeImpl.h"

namespace serial::tree
{
	template <typename T>
	inline ValueT<T>::ValueT(NODE::Node aNode, DATA::Data aData, T& arSelf)
		: Value(aNode, aData)
		, mrT(arSelf)
	{
	}

	template <typename T>
	ValueP Value::UserP(T& arSelf)
	{
		return ValueP(new UserT(arSelf));
	}


	template <typename T>
	ValueP Value::NativeP(T& arSelf)
	{
		return ValueP(new NativeT(arSelf));
	}

	template <typename T>
	ValueP Value::ArrayP(T& arSelf)
	{
		return ValueP(new ArrayT(arSelf));
	}

	template <typename T>
	ValueP Value::DictP(T& arSelf)
	{
		return ValueP(new DictT(arSelf));
	}

	template <typename T>
	ValueP Value::PairP(T& arSelf)
	{
		return ValueP(new PairT(arSelf));
	}

}

namespace serial::tree
{
	template <typename T>
	NativeT<T>::NativeT(T& arSelf)
		: ValueT<T>(NODE::Node::CHILDLESS, DATA::NATIVE, arSelf)
	{
	}

	template <typename T>
	void NativeT<T>::_Get(const serial::format::In& aF, std::istream& arIn)
	{
		arIn >> this->mrT;
	}

	template <typename T>
	void NativeT<T>::_Put(const serial::format::Out& aF, std::ostream& arOut) const
	{
		arOut << this->mrT;
	}
}

namespace serial::tree
{
	template <typename T>
	UserT<T>::UserT(T& arSelf)
		: ValueT<T>(NODE::Node::PARENT, DATA::USER, arSelf)
	{
	}

	template <typename T>
	void UserT<T>::_Get(const serial::format::In& aF, std::istream& arIn)
	{
		serial::tree::Peers d;
		serial::tree::Children(this->mrT, d);
		aF.Read(arIn, d);
	}

	template <typename T>
	void UserT<T>::_Put(const serial::format::Out& aF, std::ostream& arOut) const
	{
		serial::tree::Peers d;
		serial::tree::Children(this->mrT, d);
		aF.Write(arOut, d);
	}
}

namespace serial::tree
{
	template <typename T>
	ArrayT<T>::ArrayT(T& arSelf)
		: ValueT<T>(NODE::Node::PARENT, DATA::ARRAY, arSelf)
	{
	}

	template <typename T>
	void ArrayT<T>::_Get(const serial::format::In& aF, std::istream& arIn)
	{
		int n = T::size_type(0); ///< \todo change to auto once all the specializations available
		aF.ReadLen(arIn, Value::NativeP(n));

		this->mrT.resize(n);

		Peers d;
		for (auto it = this->mrT.begin(); it != this->mrT.end(); ++it)
		{
			serial::tree::Node(*it, d);
		}
		aF.Read(arIn, d);
	}

	template <typename T>
	void ArrayT<T>::_Put(const serial::format::Out& aF, std::ostream& arOut) const
	{
		/// \note Always provide size, however it is up to format how to handle
		int n = this->mrT.size(); ///< \todo change to auto once all the specializations available
		aF.WriteLen(arOut, Value::NativeP(n));

		Peers d;
		for (auto it = this->mrT.begin(); it != this->mrT.end(); ++it)
		{
			serial::tree::Node(*it, d);
		}

		aF.Write(arOut, d);
	}
}

namespace serial::tree
{
	template <typename T>
	DictT<T>::DictT(T& arSelf)
		: ValueT<T>(NODE::Node::PARENT, DATA::DICT, arSelf)
	{
	}

	template <typename T>
	void DictT<T>::_Get(const serial::format::In& aF, std::istream& arIn)
	{
		this->mrT.clear();

		int n = T::size_type(0); ///< \todo change to auto once all the specializations available
		aF.ReadLen(arIn, Value::NativeP(n));

		typename T::value_type v;
		auto e = serial::tree::Node(v);
		/// \todo add IsEnd query to format and incorporate into loop
		for (int i = 0; i < n; ++i)
		{			
			aF.Read(arIn, e);
			this->mrT.insert(v);
		}
	}

	template <typename T>
	void DictT<T>::_Put(const serial::format::Out& aF, std::ostream& arOut) const
	{
		int n = this->mrT.size(); ///< \todo change to auto once all the specializations available
		aF.WriteLen(arOut, Value::NativeP(n));

		Peers d;
		for (auto it = this->mrT.begin(); it != this->mrT.end(); ++it)
		{
			serial::tree::Node(*it, d);
		}
		aF.Write(arOut, d);
	}
}

namespace serial::tree
{
	template <typename T, typename U>
	PairT<T,U>::PairT(std::pair<T, U>& arSelf)
		: ValueT<std::pair<T, U>>(NODE::Node::PARENT, DATA::PAIR, arSelf)
	{
	}

	template <typename T, typename U>
	void PairT<T,U>::_Get(const serial::format::In& aF, std::istream& arIn)
	{
		/// \todo simplify below 2 lines
		auto e = serial::tree::Node(this->mrT.first);
		aF.ReadKey(arIn, e.mValueP);

		Peers d;
		serial::tree::Node(this->mrT.second, d);
		aF.Read(arIn, d);
	}

	template <typename T, typename U>
	void PairT<T,U>::_Put(const serial::format::Out& aF, std::ostream& arOut) const
	{		
		auto e = serial::tree::Node(this->mrT.first);
		aF.WriteKey(arOut, e.mValueP);

		Peers d;
		serial::tree::Node(this->mrT.second, d);
		aF.Write(arOut, d);
	}
}


#endif