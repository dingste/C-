/*! \brief PathDraw
 *
 * Implementation of a component
 *
 * File:   PathDraw.cpp
 * Author: Dieter Steuten
 *
 */

#include "PathDraw.hpp"
PathDraw::PathDraw() {}

/* --- protected functionality --- */
bool PathDraw::P(bool run) {
    data.pathData.clear();
    if (data.change_request && run) {
        /* put the processing function calls here */
        // countedExchange();
        aggregateToLine();
        return true;
    }
    return false;
}

/* private processing functions */
void PathDraw::simpleExchange() {
    // data.pathData = data.bitmapData;
}

void PathDraw::countedExchange() {
    unsigned long refcount = 0;
    data.pathData.clear();
    while (refcount < data.count) {
        //    data.pathData.push_back(data.bitmapData.at(refcount));
        refcount++;
    }
}

void PathDraw::aggregateToLine() {
    positionABS startLine = (*data.bitmapData.begin());
    positionABS endLine = startLine;
    lineABS oneLiner;
    lineDirection stayDirection = lineDirection::undefined;
    lineDirection foundDirection;

    while (!data.bitmapData.empty()) {
        foundDirection = searchDirection(endLine, stayDirection);
        endLine += foundDirection;
        if (foundDirection != lineDirection::undefined) {
            if (foundDirection != stayDirection) {
                oneLiner = {startLine, endLine, foundDirection};
                data.pathData.push_back(oneLiner);
                //      std::cout << " (" << oneLiner.line_start.X << "|" << oneLiner.line_start.Y << ")-(" << oneLiner.line_end.X << "|" << oneLiner.line_end.Y << ")" << std::endl;
                startLine = endLine;
                stayDirection = lineDirection::undefined;
            } else {
                stayDirection = foundDirection;
            }
        } else {
            // anheben
            startLine = searchNextStart(endLine);
            stayDirection = lineDirection::undefined;
            oneLiner = {endLine, startLine, stayDirection};
            data.pathData.push_back(oneLiner);
            endLine = startLine;
            //    std::cout << ";";
        }
    }
    std::cout << "Leer \n";
}

positionABS PathDraw::searchNextStart(const positionABS& beginSearch) {
    positionABS distance = beginSearch;
    // positionABS trySearch;
    auto searchIt = data.bitmapData.begin();
    auto foundIt = searchIt;
    for (; searchIt < data.bitmapData.end(); ++searchIt) {
        trySearch = {std::abs(beginSearch.X - (*searchIt).X), std::abs(beginSearch.Y - (*searchIt).Y)};
        if (trySearch.X < distance.X || trySearch.Y < distance.Y) {
            distance = trySearch;
            trySearch = {(*searchIt).X, (*searchIt).Y};
            foundIt = searchIt;
        }
    }
    data.bitmapData.erase(foundIt);
    return trySearch;
}

lineDirection PathDraw::searchDirection(const positionABS& beginSearch, const lineDirection& shouldDirection) {
    auto searchIt = data.bitmapData.begin();
    // for (std::vector::iterator<positionABS> searchIt = data.bitmapData.begin(); searchIt < data.bitmapData.end(); ++searchIt) {
    while (searchIt != data.bitmapData.end()) {
        if ((*searchIt).Y == (beginSearch.Y - 1) && (*searchIt).X == (beginSearch.X)) {
            if (shouldDirection == lineDirection::south || shouldDirection == lineDirection::undefined) {
                data.bitmapData.erase(searchIt);
                return lineDirection::south;
            } else {
                searchIt++;
            }
        } else if ((*searchIt).X == (beginSearch.X - 1) && (*searchIt).Y == (beginSearch.Y)) {
            if (shouldDirection == lineDirection::west || shouldDirection == lineDirection::undefined) {
                data.bitmapData.erase(searchIt);
                return lineDirection::west;
            } else {
                searchIt++;
            }
        } else if ((*searchIt).X == (beginSearch.X + 1) && (*searchIt).Y == (beginSearch.Y - 1)) {
            if (shouldDirection == lineDirection::south_east || shouldDirection == lineDirection::undefined) {
                data.bitmapData.erase(searchIt);
                return lineDirection::south_east;
            } else {
                searchIt++;
            }
        }

        else if ((*searchIt).X == (beginSearch.X - 1) && (*searchIt).Y == (beginSearch.Y + 1)) {
            if (shouldDirection == lineDirection::north_west || shouldDirection == lineDirection::undefined) {
                data.bitmapData.erase(searchIt);
                return lineDirection::north_west;
            } else {
                searchIt++;
            }
        } else if ((*searchIt).X == (beginSearch.X + 1) && (*searchIt).Y == (beginSearch.Y)) {
            if (shouldDirection == lineDirection::east || shouldDirection == lineDirection::undefined) {
                data.bitmapData.erase(searchIt);
                return lineDirection::east;
            } else {
                searchIt++;
            }
        } else if ((*searchIt).Y == (beginSearch.Y + 1) && (*searchIt).X == (beginSearch.X)) {
            if (shouldDirection == lineDirection::north || shouldDirection == lineDirection::undefined) {
                data.bitmapData.erase(searchIt);
                return lineDirection::north;
            } else {
                searchIt++;
            }
        } else if ((*searchIt).X == (beginSearch.X + 1) && (*searchIt).Y == (beginSearch.Y + 1)) {
            if (shouldDirection == lineDirection::north_east || shouldDirection == lineDirection::undefined) {
                data.bitmapData.erase(searchIt);
                return lineDirection::north_east;
            } else {
                searchIt++;
            }
        }

        else if ((*searchIt).X == (beginSearch.X - 1) && (*searchIt).Y == (beginSearch.Y - 1)) {
            if (shouldDirection == lineDirection::south_west || shouldDirection == lineDirection::undefined) {
                data.bitmapData.erase(searchIt);
                return lineDirection::south_west;
            } else {
                searchIt++;
            }
        }

        else if ((*searchIt).X == (beginSearch.X) && (*searchIt).Y == (beginSearch.Y)) {
            //   data.bitmapData.erase(searchIt);
            return lineDirection::undefined;
        } else {
            searchIt++;
        }
    }
    return lineDirection::undefined;
}
