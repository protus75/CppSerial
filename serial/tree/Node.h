#ifndef SERIAL_NODE_H
#define SERIAL_NODE_H

#include <string>

#include "ElemFwd.h"
#include "PeersFwd.h"

#include "NodeFwd.h"

namespace serial::tree
{
	template <typename T>
	void Children(T& arSelf, tree::Peers& arKids);

	class Connect
	{
	public:
		Connect() = default;
		virtual ~Connect() = default;

		void Children(tree::Peers& arKids);

	protected:

		virtual void _Children(tree::Peers& arKids) = 0;
	};
}

namespace serial::tree
{
	template <typename T>
	class _Children
	{
	public:
		static void Children(T& arSelf, tree::Peers& arKids);
	};
}


#include <set>
#include <map>
#include <vector>

namespace serial::tree
{
	template <typename T>
	void Node(T& arSelf, tree::Peers& arPeers);


	template <typename T>
	void Node(const std::string& aId, T & arSelf, tree::Peers& arPeers);

	
	template <typename T>
	tree::Elem Node(T& arSelf);
	
	template <typename T>
	tree::Elem Node(const T& arSelf);


	template <typename T>
	tree::Elem Node(const std::string& aId, T& arSelf);


	template <typename T>
	class _Node
	{
	public:
		/// \todo reorg methods to just have a single one to overload for ease of use
		static tree::Elem Node(T& arSelf);
		static tree::Elem Node(T& arSelf, const std::string& aId);
	};

	template <>
	tree::Elem _Node<int>::Node(int& arSelf);

	template <>
	tree::Elem _Node<int>::Node(int& arSelf, const std::string& aId);

	template <>
	tree::Elem _Node<bool>::Node(bool& arSelf);

	template <>
	tree::Elem _Node<bool>::Node(bool& arSelf, const std::string& aId);

	template <>
	tree::Elem _Node<std::string>::Node(std::string& arSelf);

	template <>
	tree::Elem _Node<std::string>::Node(std::string& arSelf, const std::string& aId);

	template <typename T>
	class _Node<std::vector<T>>
	{
	public:
		static tree::Elem Node(std::vector<T>& arSelf);
		static tree::Elem Node(std::vector<T>& arSelf, const std::string& aId);
	};

	template <typename T>
	class _Node<std::set<T>>
	{
	public:
		static tree::Elem Node(std::set<T>& arSelf);
		static tree::Elem Node(std::set<T>& arSelf, const std::string& aId);
	};

	template <typename T, typename U>
	class _Node<std::pair<T, U>>
	{
	public:
		static tree::Elem Node(std::pair<T, U>& arSelf);
		static tree::Elem Node(std::pair<T, U>& arSelf, const std::string& aId);
	};

	template <typename T, typename U>
	class _Node<std::map<T, U>>
	{
	public:
		static tree::Elem Node(std::map<T, U>& arSelf);
		static tree::Elem Node(std::map<T, U>& arSelf, const std::string& aId);
	};

}

#endif