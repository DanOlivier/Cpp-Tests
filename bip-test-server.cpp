#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <functional>
#include <utility>

int main ()
{
    using namespace boost::interprocess;

    // remove earlier existing SHM
    shared_memory_object::remove("SharedMemoryName");

    // create new 
    managed_shared_memory segment(create_only, "SharedMemoryName", 65536);

    typedef std::pair<const int, float> ValueType;

    // allocator of for the map.
    typedef allocator<ValueType, managed_shared_memory::segment_manager> ShmemAllocator;

    // third parameter argument is the ordering function is used to compare the keys.
    typedef map<int, float, std::less<int>, ShmemAllocator> MySHMMap;

    // Initialize the shared memory STL-compatible allocator
    ShmemAllocator alloc_inst(segment.get_segment_manager());

    // Construct a shared memory map.
    MySHMMap* mymap = segment.construct<MySHMMap>("MySHMMapName")(std::less<int>(), alloc_inst);

    //Insert data in the map
    for(int i = 0; i < 10; ++i)
    {
        mymap->insert(std::pair<const int, float>(i, (float)i));
    }

    return 0;
}
