#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <functional>
#include <utility>
#include <iostream>

int main ()
{
    using namespace boost::interprocess;

    try
    {
        managed_shared_memory segment(open_only, "SharedMemoryName");

        typedef std::pair<const int, float> ValueType;

        // Assign allocator 
        typedef allocator<ValueType, managed_shared_memory::segment_manager> ShmemAllocator;

        // The map
        typedef map<int, float, std::less<int>, ShmemAllocator> MySHMMap;

        // Initialize the shared memory STL-compatible allocator
        ShmemAllocator alloc_inst(segment.get_segment_manager());

        // access the map in SHM through the offset ptr                                                         
        offset_ptr<MySHMMap> m_pmap = segment.find<MySHMMap>("MySHMMapName").first;

        MySHMMap::iterator iter = m_pmap->begin();
        for(; iter != m_pmap->end(); iter++)
        {
           std::cout << iter->first << " " << iter->second << "\n";
        }
    }
    catch(std::exception& e)            
    {
        std::cout << " error  " << e.what() << std::endl;
    }
    shared_memory_object::remove("SharedMemoryName");
    return 0;
}
