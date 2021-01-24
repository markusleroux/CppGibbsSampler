//
// Created by Markus Le Roux on 2021-01-23.
//

#ifndef POTTSSAMPLER_MODEL_H
#define POTTSSAMPLER_MODEL_H

#include "Graph.h"

// TODO: t_boundinglist
//  - bounding list should be a class
//  - atMostKUp as method
//  - qComplement as method
//  - Graph::getIndexVector moved to super class

class Model : public Graph {
    private:
        std::vector<unsigned> colouring;
        std::vector<boost::dynamic_bitset<>> boundingChain;

        static boost::dynamic_bitset<> atMostKUp(boost::dynamic_bitset<> bs, unsigned int k);
        boost::dynamic_bitset<> bs_getUnfixedColours(unsigned int v) const;
        boost::dynamic_bitset<> bs_getFixedColours(unsigned int v) const;
        boost::dynamic_bitset<> UnionOfBoundingLists(const std::vector<unsigned int> &vertices) const;

    public:
        Model(unsigned int n, const std::list<std::pair<unsigned int, unsigned int>>& edges);
        int getColour(unsigned int v) const { return colouring[v]; }
        void setColour(unsigned int v, unsigned int c);

        std::vector<unsigned int> getColouring() { return colouring; }
        std::vector<unsigned int> getUnfixedColours(unsigned int v) const;
        std::vector<unsigned int> getFixedColours(unsigned int v) const;
        std::vector<unsigned int> getNeighbourhoodColourCount(unsigned int v) const;
        unsigned int m(unsigned int v, unsigned int c) const;

        boost::dynamic_bitset<> getBoundingList(unsigned int v) const { return boundingChain[v]; }
        std::vector<unsigned> getBoundingListIndex(unsigned int v) const { return getIndexVector(getBoundingList(v)); }
        void setBoundingList(unsigned int v, std::vector<unsigned int> &boundingList);
        std::vector<boost::dynamic_bitset<>> getBoundingChain() const { return boundingChain; }
        unsigned int m_Q(unsigned int v, unsigned int c) const;
        
        boost::dynamic_bitset<> bs_generateA(unsigned int v, unsigned int size) const;
};

// Overload << to print adjacency matrix
static std::ostream& operator<< (std::ostream &out, const Model &model) {
    for (unsigned v = 0; v < model.getSize(); v++) {
        out << v << " (" << model.getColour(v) << ") : [" << model.getBoundingListIndex(v) << "]\n";
    }
    return out;
}

#endif //POTTSSAMPLER_MODEL_H