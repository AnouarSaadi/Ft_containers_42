#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>

template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                // map::key_compare
           class Alloc = std::allocator< std::pair<const Key,T> >    // map::allocator_type
           > class map;

#endif