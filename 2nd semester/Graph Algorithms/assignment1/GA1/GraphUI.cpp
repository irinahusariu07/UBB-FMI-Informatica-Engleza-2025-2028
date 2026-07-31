#include "GraphUI.h"
#include <iostream>

using namespace std;

void GraphUI::start() {
//main menu - random or default 
    cout << "GRAPH PROGRAM\n";
    cout << "1. Load graph from file\n";
    cout << "2. Generate random graph\n";

    string choice;
    cout << "> ";
    cin >> choice;

    if (choice == "1") loadGraph(); 
    else if (choice == "2") generateGraph();
    else cout << "Invalid option\n";

    if (service) menu();
}

void GraphUI::loadGraph() {
    string file, mod;
    cout << "File to load graph from: ";
    cin >> file;
    cout << "File to save modifications: ";
    cin >> mod;

    try {
        // store repo pointer in the UI class
        repo = new GraphRepo(file);

        // pass repo by reference to service
        service = new GraphService(*repo, mod);

        // normalize after loading
        service->normalizeVertices();

        // save normalized version
        repo->saveModifications(repo->graph, mod);

        cout << "Graph loaded!\n";
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void GraphUI::generateGraph() {
    int v, e = -1; //by default no edges < 0 so that if user says no -> random no edges 
    cout << "Number of vertices: ";
    cin >> v;

    cout << "Do you want to specify number of edges? (y/n): ";
    char ans;
    cin >> ans;

    if (ans == 'y' || ans == 'Y') {
        cout << "Number of edges: ";
        cin >> e;
    }

    string file, mod;
    cout << "Where to save the generated graph: ";
    cin >> file;
    cout << "Where to save modifications: ";
    cin >> mod;

    //calls the external repo function for generating random 
    try {
        GraphRepo::writeRandom(file, v, e);

        GraphRepo* repo = new GraphRepo(file);
        service = new GraphService(*repo, mod);

        cout << "Random graph created!\n";
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void GraphUI::menu() {
    while (true) {
        cout << "\nMENU\n";
        cout << "1 number of vertices\n";
        cout << "2 iterate vertices\n";
        cout << "3 check edge\n";
        cout << "4 in degree\n";
        cout << "5 out degree\n";
        cout << "6 iterate outbound\n";
        cout << "7 iterate inbound\n";
        cout << "8 add vertex\n";
        cout << "9 add edge\n";
        cout << "10 remove vertex\n";
        cout << "11 remove edge\n";
        cout << "12 change cost\n";
        cout << "13 retrieve cost\n";
        cout << "14 copy graph\n";
        cout << "15 show graph representation\n";
        cout << "16 find lowest length path (reverse BFS) \n";
        cout << "17 find lowest cost walk \n";
        cout << "0 exit\n";

        string cmd;
        cout << "> ";
        cin >> cmd;

        try {
            if (cmd == "1") {
                cout << service->getVerticesNumber() << "\n";
            }
            else if (cmd == "2") {
                auto v = service->iterateVertices();
                for (int x : v) cout << x << " ";
                cout << "\n";
            }
            else if (cmd == "3") {
                int s, e;
                cout << "start: ";
                cin >> s;
                cout << "end: ";
                cin >> e;
                cout << (service->checkEdge(s, e) ? "True" : "False") << "\n";
            }
            else if (cmd == "4") {
                int v;
                cout << "vertex: ";
                cin >> v;
                cout << service->getInDegree(v) << "\n";
            }
            else if (cmd == "5") {
                int v;
                cout << "vertex: ";
                cin >> v;
                cout << service->getOutDegree(v) << "\n";
            }
            else if (cmd == "6") {
                int v;
                cout << "vertex: ";
                cin >> v;
                auto out = service->iterateOutbound(v);
                for (int x : out) cout << x << " ";
                cout << "\n";
            }
            else if (cmd == "7") {
                int v;
                cout << "vertex: ";
                cin >> v;
                auto in = service->iterateInbound(v);
                for (int x : in) cout << x << " ";
                cout << "\n";
            }
            else if (cmd == "8") {
                int v;
                cout << "new vertex id: ";
                cin >> v;
                service->addVertex(v);
            }
            else if (cmd == "9") {
                int s, e, c;
                cout << "start: ";
                cin >> s;
                cout << "end: ";
                cin >> e;
                cout << "cost: ";
                cin >> c;
                service->addEdge(s, e, c);
            }
            else if (cmd == "10") {
                int v;
                cout << "vertex: ";
                cin >> v;
                service->removeVertex(v);
            }
            else if (cmd == "11") {
                int s, e;
                cout << "start: ";
                cin >> s;
                cout << "end: ";
                cin >> e;
                service->removeEdge(s, e);
            }
            else if (cmd == "12") {
                int s, e, c;
                cout << "start: ";
                cin >> s;
                cout << "end: ";
                cin >> e;
                cout << "new cost: ";
                cin >> c;
                service->changeCost(s, e, c);
            }
            else if (cmd == "14") {
                service->copyGraph();
                cout << "Graph copied!\n";
            }
            else if (cmd == "13") {
                int s, e, c;
                cout << "start: ";
                cin >> s;
                cout << "end: ";
                cin >> e;
                c = service->retrieveCost(s, e); 
                cout << "cost: " << c; 
            }

            else if (cmd == "15"){
                cout << "Vertices: " << service->getVerticesNumber() << "\n";
                cout << "Edges:    " << service->get_costs().size() << "\n\n";

                cout << "--- Outbound adjacency lists ---\n";
                for (auto& kv : service->get_out_edges()) {
                    cout << kv.first << ": ";
                    for (int v : kv.second) cout << v << " ";
                    cout << "\n";
                }

                cout << "\n--- Inbound adjacency lists ---\n";
                for (auto& kv : service->get_in_edges()) {
                    cout << kv.first << ": ";
                    for (int v : kv.second) cout << v << " ";
                    cout << "\n";
                }

                cout << "\n--- Edge costs ---\n";
                for (auto& kv : service->get_costs()) {
                    cout << "(" << kv.first.first << ", " << kv.first.second << ")"
                        << " -> cost = " << kv.second << "\n";
                }
            }

            else if (cmd == "16")
            {
                int start, end;
                cout << "start: ";
                cin >> start;
                cout << "end: ";
                cin >> end;

                auto path = service->lowestLengthPath(start, end);

                cout << "lowest length path: ";
                for (int v : path)
                    cout << v << " ";
                cout << "\n";
                cout << "length: " << path.size() - 1 << "\n";
            }

            else if (cmd == "17")
            {
                int start, end;
                cout << "start: ";
                cin >> start;
                cout << "end: ";
                cin >> end;

                auto result = service->lowestCostWalk(start, end);
                auto path = result.first;
                int cost = result.second;

                cout << "lowest cost walk: ";
                for (int v : path)
                    cout << v << " ";
                cout << "\ntotal cost: " << cost << "\n";
            }


            else if (cmd == "0") {
                break;
            }
            else {
                cout << "Invalid command\n";
            }
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}
