#include "KDTree.h"
#include "ExtendedFunc.h"
#include "Command.h"


//int main() {
//  
//    Node* root = NULL;
//
//    string fileName = "worldcities-20210313-population-50000+.csv";
//    readFileToKDTree(fileName, root);
//
//    printTree(root);
//    //deleteTree(root);
//
//    double lat = 35.6897;
//    double lng = 139.6922;
//
//    /*if (search(root, lat, lng)) {
//        cout << "Found city with coordinates: (" << lat << ", " << lng << ")\n";
//    }
//    else {
//        cout << "City with coordinates: (" << lat << ", " << lng << ") not found\n";
//    }*/
//
//    /*cout << "KD Tree structure:" << endl;
//    printTree(root);*/
//
//    /*Point bottomLeft = { 10.0, 10.0 };
//    Point topRight = { 40.0, 150.0 };
//    
//    vector<City> citiesInRange = rangeSearch(root, bottomLeft, topRight);
//
//  
//    cout << "Cities in the specified range:" << endl;
//    for (const City& city : citiesInRange) {
//        cout << city.name << " " << city.point.x << " " << city.point.y << endl;
//    }*/
//
//   /* vector<Point> coordinates = { {41, 28.9} };
//    City nearestCity = nearestNeighborSearch(root, coordinates);
//    cout << nearestCity.name << " " << nearestCity.point.x << " " << nearestCity.point.y << endl;*/
//
//    //cout << "First" << endl;
//    ////printTree(root);
//
//    //serialize(root, "input.bin");
//    /*printTree(root);*/
//    deleteTree(root);
//
//    //root = NULL;
//    //root = deserialize("input.bin");
//    //cout << "Second" << endl;
//    //printTree(root);
//
//    //deleteTree(root);
//    ////printTree(root);
//
//	return 0;
//
//}


int main(int argc, char* argv[])
{
    Node* root = NULL;
    if (argc == 3 && string(argv[1]) == "-load") {
        if (isCSVFormat(argv[2])) {
            vector<City> data = loadCitiesFromCSV(argv[2]);
            cout << "Loading data from csv file successfully\n";
           

            for (int i = 0; i < data.size(); i++) {
                cout << data[i].name << " " << data[i].point.x << " " << data[i].point.y << "\n";
            }

            return 1;
        }
        else if (isCSVFormat(argv[2]) == false) {
            cout << "Incorrect format for loading the list of cities from a CSV file, please follow the format example below.\n";
            cout << "Load the list of cities from a CSV file. ([Execution file] -load [file name]. Ex: a.exe -load data.csv";
            return -1;
        }
    }
    else if (argc == 5 && string(argv[1]) == "-insert") {
        if (isNumber(argv[3]) && isNumber(argv[4])) {
            double lat = stringToDouble(argv[3]);
            double lng = stringToDouble(argv[4]);
            string city = string(argv[2]);
            Node* root = NULL;
            root = insert(root, city, lat, lng);
            printTree(root, 0);
            return 1;
        }
        else if (isNumber(argv[3]) == false || isNumber(argv[4]) == false) {
            cout << "Incorrect format for inserting a new city into the KD-tree, please follow the format example below.\n";
            cout << "Insert a new city into the KD-Tree. ([Execution file] -insert [City name] [Latitude] [Longitude]. Ex: a.exe -insert tokyo -35.5 139.6)";
            return -1;
        }

    }
    else if (argc == 3 && string(argv[1]) == "-insert") {
        if (isCSVFormat(argv[2])) {
            vector<City> data = loadCitiesFromCSV(argv[2]);
            
            for (int i = 0; i < data.size(); i++) {
                root = insert(root, data[i].name, data[i].point.x, data[i].point.y);
            }
            return 1;
        }
        else {
            cout << "Incorrect format for inserting multiple new cities into the KD-Tree from a specified CSV file path, please follow the format example below.\n";
            cout << "Insert multiple new cities into the KD-Tree from a specified CSV file path. ([Execution file] -insert [file name]. Ex: a.exe -insert data.csv)";
            return -1;
        }
    }

    else if (string(argv[1]) == "-query") {
        if (argc == 7 && isNumber(argv[2]) && isNumber(argv[3]) && isNumber(argv[4]) && isNumber(argv[5]) && string(argv[6]) == "-console") {
            //ham xuat ket qua truy van vung chu nhat ra man hinh;
            Point a, b, bottomLeft, topRight;

            a.x = stringToDouble(argv[2]);
            a.y = stringToDouble(argv[3]);

            b.x = stringToDouble(argv[4]);
            b.y = stringToDouble(argv[5]);

            distinguishPoints(a, b, bottomLeft, topRight);

            vector<City> citiesInRange = rangeSearch(root, bottomLeft, topRight);

            for (int i = 0; i < citiesInRange.size(); i++) {
                cout << "City: " << citiesInRange[i].name << ", Latitude: " << citiesInRange[i].point.x << ", Longitude: " << citiesInRange[i].point.y << endl;
            }

            return 1;
        }
        else if (argc == 8 && isNumber(argv[2]) && isNumber(argv[3]) && isNumber(argv[4]) && isNumber(argv[5]) && isCSVFormat(argv[6]) && string(argv[7]) == "-file") {

            Point a, b, bottomLeft, topRight;

            a.x = stringToDouble(argv[2]);
            a.y = stringToDouble(argv[3]);

            b.x = stringToDouble(argv[4]);
            b.y = stringToDouble(argv[5]);

            distinguishPoints(a, b, bottomLeft, topRight);

            vector<City> citiesInRange = rangeSearch(root, bottomLeft, topRight);
            writeCitiesToCSVFilee(string(argv[6]), citiesInRange);


        }
        else if (argc == 8 && isNumber(argv[2]) && isNumber(argv[3]) && isNumber(argv[4]) && isNumber(argv[5]) && isCSVFormat(argv[6]) && string(argv[7]) == "-both") {

            Point a, b, bottomLeft, topRight;

            a.x = stringToDouble(argv[2]);
            a.y = stringToDouble(argv[3]);

            b.x = stringToDouble(argv[4]);
            b.y = stringToDouble(argv[5]);

            distinguishPoints(a, b, bottomLeft, topRight);

            vector<City> citiesInRange = rangeSearch(root, bottomLeft, topRight);

            writeCitiesToCSVFilee(string(argv[6]), citiesInRange);

        }
        else {
            cout << "Incorrect format for Query all cities within a specified rectangular region defined by its geographical boundaries,please follow the format example below.\n";
            cout << "      - Protocol for outputting results to the screen: [Execution file] -query [min_latitude] [max_latitude] [min_longitude] [max_longitude] -console.\n";
            cout << "        Ex: a.exe -query 10 10.7 105 107 -console\n";
            cout << "      - Protocol for outputing results to CSV file: [Execution file] -query [min_latitude] [max_latitude] [min_longitude] [max_longitude] [filename] -file.\n";
            cout << "        Ex: a.exe -query 10 10.7 105 107 result.csv -file\n";
            cout << "      - Protocol for outputting results to the screen and csv file: [Execution file] -query [min_latitude] [max_latitude] [min_longitude] [max_longitude] [filename] -both.\n";
            cout << "        Ex: a.exe -query 10 10.7 105 107 result.csv -both\n";
        }
    }
    else if (string(argv[1]) == "-find") {
        if (argc <= 4 && argc % 2 == 0) {
            cout << "Incorrect format";
            return -1;
        }
        else if (string(argv[argc - 1]) == "-console") {
            int n = (argc - 3) / 2;

            vector<Point> coordinates;

            int index = 2;
            for (int i = 0; i < n; i++) {
                Point temp;
                temp.x = stringToDouble(argv[index]);
                index++;
                temp.y = stringToDouble(argv[index]);
                index++;

                coordinates.push_back(temp);

            }
            City nearestCity = nearestNeighborSearch(root, coordinates);
            cout << nearestCity.name << " " << nearestCity.point.x << " " << nearestCity.point.y << endl;

        }
        else if ((string(argv[argc - 1]) == "-file" || string(argv[argc - 1]) == "-both") && isCSVFormat(string(argv[argc - 2]))) {
            int n = (argc - 4)/2;

            vector<Point> coordinates;

            int index = 2;
            for (int i = 0; i < n; i++) {
                Point temp;
                temp.x = stringToDouble(argv[index]);
                index++;
                temp.y = stringToDouble(argv[index]);
                index++;

                coordinates.push_back(temp);

            }
            City nearestCity = nearestNeighborSearch(root, coordinates);
            if (string(argv[argc - 1]) == "-file") {
                writeCityToCSVFile(string(argv[argc - 2]), nearestCity);

            }
            else if (string(argv[argc - 1]) == "-both") {
                cout << nearestCity.name << " " << nearestCity.point.x << " " << nearestCity.point.y << endl;
                writeCityToCSVFile(string(argv[argc - 2]), nearestCity);
            }

        }
       
    }

    else {
        cout << "Please select the options corresponding to the command line patterns.\n";
        cout << "1. Load the list of cities from a CSV file. ([Execution file] -load [file name]. Ex: a.exe -load data.csv)\n";
        cout << "2. Insert a new city into the KD-Tree. ([Execution file] -insert [City name] [Lat] [Ing]. Ex: a.exe -insert tokyo -35.5 139.6)\n";
        cout << "3. Insert multiple new cities into the KD-Tree from a specified CSV file path. ([Execution file] -insert [file name]. Ex: a.exe -insert data.csv)\n";
        cout << "4. Conduct a nearest neighbor search by providing latitude and longitude coordinates.\n";
        cout << "      - Protocol for outputting results to the screen: [Execution file] -find [Latitude] [Longitude] -console. Ex: a.exe -find -35.02 65.5 -console\n";
        cout << "      - Protocol for outputing results to CSV file: [Execution file] -find [Latitude] [Longitude] [filename] -file. Ex: a.exe -find -35.02 65.5 result.csv -file\n";
        cout << "      - Protocol for outputting results to the screen and csv file: [Execution file] -find [Latitude] [Longitude] [filename] -both. Ex: a.exe -find -35.02 65.5 result.csv -both\n";
        cout << "5. Query all cities within a specified rectangular region defined by its geographical boundaries.\n";
        cout << "      - Protocol for outputting results to the screen: [Execution file] -query [min_latitude] [max_latitude] [min_longitude] [max_longitude] -console.\n";
        cout << "        Ex: a.exe -query 10 10.7 105 107 -console\n";
        cout << "      - Protocol for outputing results to CSV file: [Execution file] -query [min_latitude] [max_latitude] [min_longitude] [max_longitude] [filename] -file.\n";
        cout << "        Ex: a.exe -query 10 10.7 105 107 result.csv -file\n";
        cout << "      - Protocol for outputting results to the screen and csv file: [Execution file] -query [min_latitude] [max_latitude] [min_longitude] [max_longitude] [filename] -both.\n";
        cout << "        Ex: a.exe -query 10 10.7 105 107 result.csv -both\n";
    }


    return 0;
}