#include <iostream>
#include <queue>
#include <utility>

struct HeapSwapIterator
{
	int itemP;
	int itemC;
};

inline int heapParent( int i ) { return ( i - 1 ) / 2; }
inline int heapChildL( int i ) { return 2 * i + 1; }
inline int heapChildR( int i ) { return 2 * ( i + 1 ); }

// Put new data at the last element before loop
HeapSwapIterator heapPushBegin( int n )
{
	HeapSwapIterator it;
	it.itemC = n - 1;
	it.itemP = heapParent( it.itemC );
	return it;
}
bool heapPushIsEnd( const int* heapKeys, HeapSwapIterator it )
{
	if( it.itemC <= 0 )
	{
		return true;
	}

	int valueC = heapKeys[it.itemC];
	int valueP = heapKeys[it.itemP];
	if( valueP <= valueC )
	{
		return true;
	}
	return false;
}
HeapSwapIterator heapPushNext( HeapSwapIterator it )
{
	HeapSwapIterator next;
	next.itemC = it.itemP;
	next.itemP = heapParent( next.itemC );
	return next;
}

bool heapPopIsEnd( const int* heapKeys, int heapCount, HeapSwapIterator it )
{
	if( heapCount <= it.itemC )
	{
		return true;
	}

	int valueC = heapKeys[it.itemC];
	int valueP = heapKeys[it.itemP];
	if( valueP <= valueC )
	{
		return true;
	}
	return false;
}
HeapSwapIterator heapPopNext( const int* heapKeys, int heapCount, HeapSwapIterator it )
{
	int itemL = heapChildL( it.itemC );
	int itemR = itemL + 1;

	HeapSwapIterator next;
	next.itemP = it.itemC;
	if( heapCount <= itemR )
	{
		next.itemC = itemL;
	}
	else
	{
		int L = heapKeys[itemL];
		int R = heapKeys[itemR];
		next.itemC = L < R ? itemL : itemR;
	}
	return next;
}
// Put the last element to the top at the last element before loop
HeapSwapIterator heapPopBegin( const int* heapKeys, int heapCount )
{
	HeapSwapIterator it;
	it.itemC = 0;
	it.itemP = 0;
	return heapPopNext( heapKeys, heapCount, it );
}

int main()
{
	for( int i = 0; i < 10000; ++i )
	{
		std::priority_queue<int, std::vector<int>, std::greater<int>> pQue;
		int heapKeys[1000];
		int heapCount = 0;

		int N = rand() % 1000;

		for( int i = 0; i < N; ++i )
		{
			int v = rand();
			heapKeys[heapCount++] = v;
			pQue.push( v );

			for( HeapSwapIterator it = heapPushBegin( heapCount ); !heapPushIsEnd( heapKeys, it ); it = heapPushNext( it ) )
			{
				std::swap( heapKeys[it.itemC], heapKeys[it.itemP] );
			}
		}
		for( int i = 0; i < N; ++i )
		{
			int v = heapKeys[0];
			heapKeys[0] = heapKeys[--heapCount];
			for( HeapSwapIterator it = heapPopBegin( heapKeys, heapCount ); !heapPopIsEnd( heapKeys, heapCount, it ); it = heapPopNext( heapKeys, heapCount, it ) )
			{
				std::swap( heapKeys[it.itemC], heapKeys[it.itemP] );
			}

			if( pQue.top() != v )
			{
				printf( "failure: %d != %d\n", pQue.top(), v );
			}
			pQue.pop();
		}
	}
	return 0;
}
