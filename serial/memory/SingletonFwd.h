#ifndef SERIAL_MEMORY_SINGLETON_FWD_H
#define SERIAL_MEMORY_SINGLETON_FWD_H

namespace serial::memory
{
template <typename T> class Singleton;

template <typename T> T& Instance();

template <typename T> T& Delete();

template <typename T> class SingletonImpl;
}

#endif