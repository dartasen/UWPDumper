#pragma once

#include <array>
#include <atomic>
#include <thread>

template< typename QueueType, std::size_t PoolSize >
class AtomicQueue
{
	public:
		using Type = QueueType;
		static constexpr std::size_t MaxSize = PoolSize;

		AtomicQueue() : Head(0), Tail(0)
		{ }

		~AtomicQueue() = default;

		void Enqueue(const Type& Entry)
		{
			while (Mutex.test_and_set(std::memory_order_acquire))
			{
				std::this_thread::yield();
			}

			Entries[Tail] = Entry;
			Tail = (Tail + 1) % MaxSize;
			Mutex.clear(std::memory_order_release);
		}

		Type Dequeue()
		{
			while (Mutex.test_and_set(std::memory_order_acquire))
			{
				std::this_thread::yield();
			}

			Type Temp = Entries[Head];
			Head = (Head + 1) % MaxSize;
			Mutex.clear(std::memory_order_release);
			return Temp;
		}

		std::size_t Size()
		{
			while (Mutex.test_and_set(std::memory_order_acquire))
			{
				std::this_thread::yield();
			}

			Mutex.clear(std::memory_order_release);
			const std::size_t Result = Tail - Head;
			return Result;
		}

		bool Empty()
		{
			return Size() == 0;
		}

	private:
		std::array<Type, MaxSize> Entries = { Type() };
		std::size_t Head = 0;
		std::size_t Tail = 0;
		std::atomic_flag Mutex = ATOMIC_FLAG_INIT;
};