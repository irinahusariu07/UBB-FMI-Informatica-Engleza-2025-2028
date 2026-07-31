#pragma once
#include "GraphService.h"

class GraphUI {
private:
    GraphRepo* repo = nullptr;
    GraphService* service = nullptr;

public:
    void start();
    void loadGraph();
    void generateGraph();
    void menu();
};
