//
// Created by lilelr on 12/20/17.
//

#ifndef ALISIMULATOR_COLLECTION_HELPER_H
#define ALISIMULATOR_COLLECTION_HELPER_H

#include <iostream>
#include <glog/logging.h>

namespace AliSim {


// Perform a lookup in a map or hash_map.
// If the key is present in the map then the value associated with that
// key is returned, otherwise the value passed as a default is returned.
    template <class Collection>
    const typename Collection::value_type::second_type&
    FindWithDefault(const Collection& collection,
                    const typename Collection::value_type::first_type& key,
                    const typename Collection::value_type::second_type& value) {
        typename Collection::const_iterator it = collection.find(key);
        if (it == collection.end()) {
            return value;
        }
        return it->second;
    }

// Perform a lookup in a map or hash_map.
// If the key is present a const pointer to the associated value is returned,
// otherwise a NULL pointer is returned.
    template <class Collection>
    const typename Collection::value_type::second_type*
    FindOrNull(const Collection& collection,
               const typename Collection::value_type::first_type& key) {
        typename Collection::const_iterator it = collection.find(key);
        if (it == collection.end()) {
            return 0;
        }
        return &it->second;
    }

// Perform a lookup in a map or hash_map.
// Same as above but the returned pointer is not const and can be used to change
// the stored value.
    template <class Collection>
    typename Collection::value_type::second_type*
    FindOrNull(Collection& collection,  // NOLINT
               const typename Collection::value_type::first_type& key) {
        typename Collection::iterator it = collection.find(key);
        if (it == collection.end()) {
            return 0;
        }
        return &it->second;
    }

// Perform a lookup in a map or hash_map whose values are pointers.
// If the key is present a const pointer to the associated value is returned,
// otherwise a NULL pointer is returned.
// This function does not distinguish between a missing key and a key mapped
// to a NULL value.
    template <class Collection>
    const typename Collection::value_type::second_type
    FindPtrOrNull(const Collection& collection,
                  const typename Collection::value_type::first_type& key) {
        typename Collection::const_iterator it = collection.find(key);
        if (it == collection.end()) {
            return 0;
        }
        return it->second;
    }

// Change the value associated with a particular key in a map or hash_map.
// If the key is not present in the map the key and value are inserted,
// otherwise the value is updated to be a copy of the value provided.
// True indicates that an insert took place, false indicates an update.
    template <class Collection, class Key, class Value>
    bool InsertOrUpdate(Collection * const collection,
                        const Key& key, const Value& value) {
        std::pair<typename Collection::iterator, bool> ret =
                collection->insert(typename Collection::value_type(key, value));
        if (!ret.second) {
            // update
            ret.first->second = value;
            return false;
        }
        return true;
    }

// Insert a new key and value into a map or hash_map.
// If the key is not present in the map the key and value are
// inserted, otherwise nothing happens. True indicates that an insert
// took place, false indicates the key was already present.
    template <class Collection, class Key, class Value>
    bool InsertIfNotPresent(Collection * const collection,
                            const Key& key, const Value& value) {
        std::pair<typename Collection::iterator, bool> ret =
                collection->insert(typename Collection::value_type(key, value));
        return ret.second;
    }

// Perform a lookup in map or hash_map.
// If the key is present and value is non-NULL then a copy of the value
// associated with the key is made into *value. Returns whether key was present.
    template <class Collection, class Key, class Value>
    bool FindCopy(const Collection& collection,
                  const Key& key,
                  Value* const value) {
        typename Collection::const_iterator it = collection.find(key);
        if (it == collection.end()) {
            return false;
        }
        if (value) {
            *value = it->second;
        }
        return true;
    }

// Test to see if a set, map, hash_set or hash_map contains a particular key.
// Returns true if the key is in the collection.
    template <class Collection, class Key>
    bool ContainsKey(const Collection& collection, const Key& key) {
        typename Collection::const_iterator it = collection.find(key);
        return it != collection.end();
    }

    template <class Collection>
    const typename Collection::value_type::second_type&
    FindOrDie(const Collection& collection,
              const typename Collection::value_type::first_type& key) {
        typename Collection::const_iterator it = collection.find(key);
        CHECK(it != collection.end()) << "Map key not found: " << key;
        return it->second;
    }
}


#endif //ALISIMULATOR_COLLECTION_HELPER_H
