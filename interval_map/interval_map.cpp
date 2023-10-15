#pragma once
#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K, V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
		: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		if (!(keyBegin < keyEnd))
		{
			//do nothing
		}
		else
		{
			if (!m_map.empty())
			{
				auto begin_lowerb_it = m_map.lower_bound(keyBegin);
				auto end_lowerb_it = m_map.lower_bound(keyEnd);
				if ((begin_lowerb_it == m_map.begin()) && (end_lowerb_it == m_map.end()))
				{
					if (!(val == m_valBegin))
					{
						//erase all pairs in m_map
						m_map.clear();
						m_map.emplace(keyBegin, val);
						m_map.emplace(keyEnd, m_valBegin);
					}
					else
					{
						//erase all pairs in m_map
						m_map.clear();
					}
				}
				else if ((begin_lowerb_it == m_map.begin()) && (end_lowerb_it == m_map.begin()))
				{
					if (!(val == m_valBegin))
					{
						m_map.emplace(keyBegin, val);
						m_map.emplace(keyEnd, m_valBegin);
					}
					else
					{
						//do nothing
					}
				}
				else if ((begin_lowerb_it == m_map.end()) && (end_lowerb_it == m_map.end()))
				{
					auto it = m_map.end();
					auto lastVal = (--it)->second;
					if ( !(val == lastVal) )
					{
						m_map.emplace(keyBegin, val);
						m_map.emplace(keyEnd, lastVal);
					}
					else
					{
						//do nothing
					}
				}
				else if ((begin_lowerb_it != m_map.end()) && (end_lowerb_it == m_map.end()))
				{
					auto it = m_map.end();
					V lastVal = (--it)->second;
					if (!(val == lastVal))
					{
						m_map.erase(it->first);
						m_map.emplace(keyBegin, val);
						m_map.emplace(keyEnd, lastVal);
					}
					else
					{
						//do nothing
					}
				}
				else if ((begin_lowerb_it == m_map.begin()) && (end_lowerb_it != m_map.begin()))
				{
					auto it = m_map.begin();
					V firstVal = it->second;
					if (!(val == firstVal))
					{
						m_map.erase(it->first);
						if (!(val == m_valBegin))
						{
							m_map.emplace(keyBegin, val);
							m_map.emplace(keyEnd, firstVal);
						}
						else
						{
							m_map.emplace(keyEnd, firstVal);
						}
					}
					else
					{
						m_map.erase(it->first);
						if (!(val == m_valBegin))
						{
							m_map.emplace(keyBegin, val);
							m_map.emplace(keyEnd, val);
						}
						else
						{
							m_map.emplace(keyEnd, val);
						}
					}
				}
				else
				{
					if (begin_lowerb_it == end_lowerb_it)
					{
						if (!(end_lowerb_it->first < keyEnd) && !(keyEnd < end_lowerb_it->first))
						{
							//do nothing
						}
						else
						{
							const auto& value = (--end_lowerb_it)->second;
							if (value == val)
							{
								//do nothing
							}
							else
							{
								m_map.emplace(keyBegin, val);
								m_map.emplace(keyEnd, value);
							}
						}
					}
					else if (begin_lowerb_it->first < end_lowerb_it->first)
					{
						V lastValue = begin_lowerb_it->second;
						//Check if keys are equal
						if (!(begin_lowerb_it->first < keyBegin) && !(keyBegin < begin_lowerb_it->first))
						{
							if (begin_lowerb_it->second == val)
							{
								//do nothing
							}
							else
							{
								begin_lowerb_it->second = val;
							}
						}
						else
						{

							--begin_lowerb_it;
							if (begin_lowerb_it->second == val)
							{
								++begin_lowerb_it;
							}
							else
							{
								m_map.emplace(keyBegin, val);
								++begin_lowerb_it;
							}
							
						}
						++begin_lowerb_it;

						//iterate through pairs as long as they are strictly less than endKey and not at the end, and remove them after storing their value
						while ((begin_lowerb_it->first < end_lowerb_it->first) || (end_lowerb_it->first < begin_lowerb_it->first))
						{
							if (begin_lowerb_it->first < keyEnd)
							{
								lastValue = begin_lowerb_it->second;
								begin_lowerb_it = m_map.erase(begin_lowerb_it);
							}
						}
						//add pair
						if (!(lastValue == end_lowerb_it->second))
						{
							if (!(lastValue == val))
							{
								m_map.emplace(keyEnd, lastValue);
							}
						}
						
					}
				}
				
			}
			else
			{
				//map empty
				if (!(val == m_valBegin))
				{
					m_map.emplace(keyBegin, val);
					m_map.emplace(keyEnd, m_valBegin);
				}
			}
		}

	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin()) {
			return m_valBegin;
		}
		else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.
