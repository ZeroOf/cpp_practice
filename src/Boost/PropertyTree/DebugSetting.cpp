
#include "DebugSetting.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

namespace pt = boost::property_tree;

void DebugSetting::load(const std::string &filename) {
    // Create empty property tree object
    pt::ptree tree;

    // Parse the XML into the property tree.
    pt::read_xml(filename, tree);

    // Use the throwing version of get to find the debug filename.
    // If the path cannot be resolved, an exception is thrown.
    file_ = tree.get<std::string>("debug.filename");
    pt::ptree subTree = tree.get_child("debug.filename");
    std::cout << subTree.size() << std::endl;

    // Use the default-value version of get to find the debug level.
    // Note that the default value is used to deduce the target type.
    level_ = tree.get("debug.level", 0);

    // Use get_child to find the node containing the modules, and iterate over
    // its children. If the path cannot be resolved, get_child throws.
    // A C++11 for-range loop would also work.
    BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("debug.modules")) {
                    // The data function is used to access the data stored in a node.
                    modules_.insert(v.second.data());
                }
}

void DebugSetting::save(const std::string &filename) {
    // Create an empty property tree object.
    pt::ptree tree;

    // Put the simple values into the tree. The integer is automatically
    // converted to a string. Note that the "debug" node is automatically
    // created if it doesn't exist.
    tree.put("debug.filename", file_);
    tree.put("debug.level", level_);

    // Add all the modules. Unlike put, which overwrites existing nodes, add
    // adds a new node at the lowest level, so the "modules" node will have
    // multiple "module" children.
    BOOST_FOREACH(const std::string &name, modules_)tree.add("debug.modules.module", name);

    // Write property tree to XML file
    pt::write_xml(filename, tree, std::locale(),
                  pt::xml_writer_settings<std::string>(' ', 4));
}
