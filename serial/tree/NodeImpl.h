#ifndef SERIAL_NODEIMPL_H
#define SERIAL_NODEIMPL_H

#include "Node.h"

#include <vector>
#include <set>
#include <map>

#include "Key.h"
#include "ValueImpl.h"
#include "ElemImpl.h"
#include "PeersImpl.h"

namespace serial::tree
{
	template <typename T>
	inline void _Children<T>::Children(T& arSelf, Peers& arKids)
	{
		arSelf.Children(arKids);
	}

	template <typename T>
	inline void Children(T& arSelf, Peers& arKids)
	{
		_Children<T>::Children(arSelf, arKids);
	}
}

namespace serial::tree
{
	template <typename T>
	inline Elem _Node<T>::Node(T& arSelf)
	{
		return Elem(Key::User(), Value::UserP(arSelf));
	}

	template <typename T>
	inline Elem _Node<T>::Node(T& arSelf, const std::string& aId)
	{
		return Elem(Key(aId), Value::UserP(arSelf));
	}

	template <typename T>
	inline Elem _Node<std::vector<T>>::Node(std::vector<T>& arSelf)
	{
		return Elem(Key::Array(), Value::ArrayP(arSelf));
	}

	template <typename T>
	inline Elem _Node<std::vector<T>>::Node(std::vector<T>& arSelf, const std::string& aId)
	{
		return Elem(Key(aId), Value::ArrayP(arSelf));
	}

	template <typename T>
	inline Elem _Node<std::set<T>>::Node(std::set<T>& arSelf)
	{
		return Elem(Key::Dict(), Value::DictP(arSelf));
	}

	template <typename T>
	inline Elem _Node<std::set<T>>::Node(std::set<T>& arSelf, const std::string& aId)
	{
		return Elem(Key(aId), Value::DictP(arSelf));
	}

	template <typename T, typename U>
	inline Elem _Node<std::pair<T, U>>::Node(std::pair<T, U>& arSelf)
	{
		return Elem(Key::Pair(), Value::PairP(arSelf));
	}

	template <typename T, typename U>
	inline Elem _Node<std::pair<T, U>>::Node(std::pair<T, U>& arSelf, const std::string& aId)
	{
		return Elem(Key(aId), Value::PairP(arSelf));
	}

	template <typename T, typename U>
	inline Elem _Node<std::map<T, U>>::Node(std::map<T, U>& arSelf)
	{
		return Elem(Key::Dict(), Value::DictP(arSelf));
	}

	template <typename T, typename U>
	inline Elem _Node<std::map<T, U>>::Node(std::map<T, U>& arSelf, const std::string& aId)
	{
		return Elem(Key(aId), Value::DictP(arSelf));
	}
}

namespace serial::tree
{
	template <typename T>
	inline Elem Node(T& arSelf)
	{
		return _Node<T>::Node(arSelf);
	}

	template <typename T>
	inline Elem Node(const T& arSelf)
	{
		return _Node<T>::Node(const_cast<T&>(arSelf));
	}


	template <typename T>
	inline void Node(T& arSelf, Peers& arPeers)
	{
		arPeers.mItems.emplace_back(Node(arSelf));
	}


	template <typename T>
	inline Elem Node(const std::string& aId, T& arSelf)
	{
		return _Node<T>::Node(arSelf, aId);
	}


	template <typename T>
	inline void Node(const std::string& aId, T& arSelf, Peers& arPeers)
	{
		arPeers.mItems.emplace_back(Node(aId, arSelf));
	}
}


#endif
