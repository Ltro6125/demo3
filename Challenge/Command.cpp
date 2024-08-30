#include "Command.h"

vector<City> loadCitiesFromCSV(string filename) {
    vector<City> cities;
    ifstream file(filename.c_str());
    if (!file) {
        cout << "can't open file";
        return cities;
    }
    string line, word;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        City city;
        getline(ss, city.name, ',');
        ss >> city.point.x;
        ss.ignore(); 
        ss >> city.point.y;

        cities.push_back(city);
    }
    return cities;
}

double stringToDouble(const std::string& str) {
    double result;
    stringstream ss(str);
    ss >> result;
    return result;
}

void distinguishPoints(Point& point1, Point& point2, Point& bottomLeft, Point& topRight) {
    if (point1.x < point2.x && point1.y < point2.y) {
        bottomLeft = point1;
        topRight = point2;
    }
    else if (point1.x > point2.x && point1.y > point2.y) {
        bottomLeft = point2;
        topRight = point1;
    }
    else {

        if (point1.x < point2.x) {
            bottomLeft = point1;
            topRight = point2;
        }
        else {
            bottomLeft = point2;
            topRight = point1;
        }
    }
}

bool isCSVFormat(string filename) {
    if (filename.length() < 4) {
        return false;
    }

    string extension = filename.substr(filename.length() - 4);
    return extension == ".csv";
}
bool isNumber(string str) {
    bool decimalPoint = false;
    int start = 0;


    if (str[start] == '-') {
        start++;
        if (str.size() == 1) {
            return false;
        }
    }


    for (int i = start; i < str.size(); i++) {
        if (str[i] == '.') {
            if (decimalPoint) {
                return false;
            }
            decimalPoint = true;
        }
        else if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void writeCitiesToCSVFilee(string fileName, vector<City> cities) {
    ofstream ofs(fileName);

    if (!ofs) {
        cout << "Khong doc duoc file " << fileName;
        return;
    }
    ofs << "city,lat,lng\n";

    for (int i = 0; i < cities.size(); i++) {
        ofs << cities[i].name << "," << cities[i].point.x << "," << cities[i].point.y << endl;
    }

    ofs.close();

}

void writeCityToCSVFile(string fileName, City city) {
    ofstream ofs(fileName);

    if (!ofs) {
        cout << "Khong doc duoc file " << fileName;
        return;
    }
    ofs << "city,lat,lng\n";

    ofs << city.name << "," << city.point.x << "," << city.point.y << endl;

    ofs.close();
}
