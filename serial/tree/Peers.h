#ifndef SERIAL_TREE_PEERS_H
#define SERIAL_TREE_PEERS_H

#include <vector>

#include "Elem.h"

#include "PeersFwd.h"

namespace serial::tree
{
	class Peers
	{
	public:
		typedef std::vector<Elem> TStorage;

		TStorage mItems;

		Peers() = default;

		size_t Len() const;

	private:
		Peers(const TStorage& mItems) = delete;

		bool operator==(const Peers& other) const = delete;
	};


}

#endif


