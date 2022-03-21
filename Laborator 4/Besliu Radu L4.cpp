// 1
//#include <iostream>
//#include <vector>
//
//using std::cout, std::cin, std::vector, std::string;
//
//class Student {
//    string nume, prenume;
//    int grupa, semigrupa, n;
//    vector < int > note;
//
//public:
//    Student(const string &nume, const string &prenume, int grupa, int semigrupa, int n, const vector<int> &note);
//
//    Student();
//
//    friend std::istream &operator>>(std::istream &is, Student &student);
//    friend std::ostream &operator<<(std::ostream &os, const Student &student);
//    friend void operator+=(Student& student, const int notaNoua);
//
//    const string &getNume() const;
//
//    void setNume(const string &nume);
//
//    const string &getPrenume() const;
//
//    void setPrenume(const string &prenume);
//
//    int getN() const;
//
//    void setN(int n);
//
//    int getGrupa() const;
//
//    void setGrupa(int grupa);
//
//    int getSemigrupa() const;
//
//    void setSemigrupa(int semigrupa);
//
//    const vector<int> &getNote() const;
//
//    void setNote(const vector<int> &note);
//};
//
//const string &Student::getNume() const {
//    return nume;
//}
//
//void Student::setNume(const string &nume) {
//    Student::nume = nume;
//}
//
//const string &Student::getPrenume() const {
//    return prenume;
//}
//
//void Student::setPrenume(const string &prenume) {
//    Student::prenume = prenume;
//}
//
//int Student::getGrupa() const {
//    return grupa;
//}
//
//void Student::setGrupa(int grupa) {
//    Student::grupa = grupa;
//}
//
//int Student::getSemigrupa() const {
//    return semigrupa;
//}
//
//void Student::setSemigrupa(int semigrupa) {
//    Student::semigrupa = semigrupa;
//}
//
//const vector<int> &Student::getNote() const {
//    return note;
//}
//
//void Student::setNote(const vector<int> &note) {
//    Student::note = note;
//}
//std::istream &operator>>(std::istream &is, Student &student) {
//    int x;
//    is >> student.n >> student.grupa >> student.semigrupa;
//    for (int i = 0; i < student.n; ++i) {
//        is >> x;
//        student.note.emplace_back(x);
//    }
//    is.get();
//    is >> student.nume;
//    is >> student.prenume;
//    return is;
//}
//
//std::ostream &operator<<(std::ostream &os, const Student &student) {
//    os << "nume: " << student.nume << " prenume: " << student.prenume << " grupa: " << student.grupa << " semigrupa: "
//       << student.semigrupa << " note: ";
//    for (const & nota : student.note) {
//        os << nota << " ";
//    }
//    os << '\n' << "n: " << student.n << '\n';
//    return os;
//}
//
//int Student::getN() const {
//    return n;
//}
//
//void Student::setN(int n) {
//    Student::n = n;
//}
//
//Student::Student(const string &nume, const string &prenume, int grupa, int semigrupa, int n, const vector<int> &note)
//        : nume(nume), prenume(prenume), grupa(grupa), semigrupa(semigrupa), n(n), note(note) {}
//
//Student::Student() {
//    nume = prenume = "";
//    grupa = semigrupa = n;
//    note = {};
//}
//
//void operator+=(Student& student, int notaNoua) {
//    student.note.emplace_back(notaNoua);
//    student.n += 1;
//}
//
//int main() {
//    Student student;
//    cin >> student;
//    cout << student;
//    student += 5;
//    cout << student;
//}

// 2
//#include <iostream>
//#include <vector>
//
//int nrProd;
//
//using std::cin, std::cout, std::ostream, std::istream, std::vector, std::getline, std::string;
//
//class ConstructionProduct {
//    int cantitate;
//    double pret;
//    string nume, um;
//
//public:
//    friend istream &operator>>(istream &is, ConstructionProduct &produs);
//
//    friend ostream &operator<<(ostream &os, const ConstructionProduct &product);
//
//    friend ConstructionProduct operator++(ConstructionProduct &produs);
//
//    friend ConstructionProduct operator+=(ConstructionProduct &produs, const int addCantitate);
//
//    int getCantitate() const;
//
//    void setCantitate(int cantitate);
//
//    double getPret() const;
//
//    void setPret(double pret);
//
//    const string &getNume() const;
//
//    void setNume(const string &nume);
//
//    const string &getUm() const;
//
//    void setUm(const string &um);
//};
//
//int ConstructionProduct::getCantitate() const {
//    return cantitate;
//}
//
//void ConstructionProduct::setCantitate(int cantitate) {
//    ConstructionProduct::cantitate = cantitate;
//}
//
//double ConstructionProduct::getPret() const {
//    return pret;
//}
//
//void ConstructionProduct::setPret(double pret) {
//    ConstructionProduct::pret = pret;
//}
//
//const string &ConstructionProduct::getNume() const {
//    return nume;
//}
//
//void ConstructionProduct::setNume(const string &nume) {
//    ConstructionProduct::nume = nume;
//}
//
//const string &ConstructionProduct::getUm() const {
//    return um;
//}
//
//void ConstructionProduct::setUm(const string &um) {
//    ConstructionProduct::um = um;
//}
//
//istream &operator>>(istream &is, ConstructionProduct &produs) {
//    cout << "nume: ";
//    getline(is, produs.nume);
//    cout << "unitate masura: ";
//    getline(is, produs.um);
//    cout << "cantitate: ";
//    is >> produs.cantitate;
//    cout << "pret: ";
//    is >> produs.pret;
//    return is;
//}
//
//ostream &operator<<(ostream &os, const ConstructionProduct &product) {
//    os << "cantitate: " << product.cantitate << " pret: " << product.pret << " nume: " << product.nume << " um: "
//       << product.um;
//    return os;
//}
//
//ConstructionProduct operator++(ConstructionProduct &produs) {
//    produs.cantitate += 1;
//    return produs;
//}
//
//ConstructionProduct operator+=(ConstructionProduct &produs, const int addCantitate) {
//    produs.cantitate += addCantitate;
//    return produs;
//}
//
//void afisareChitanta(const vector < ConstructionProduct > &produse) {
//    double totalSum = 0;
//    for (int i = 0; i < nrProd; ++i) {
//        cout << i + 1 << ". ";
//        cout << produse[i].getNume() << " (" << produse[i].getUm() << ") x " << produse[i].getCantitate() << '\n';
//        cout << "   " << produse[i].getCantitate() << " x " << produse[i].getPret() << " = " << (double)produse[i].getCantitate() * produse[i].getPret() << " RON\n";
//        totalSum += (double)produse[i].getCantitate() * produse[i].getPret();
//    }
//    cout << "---\n";
//    cout << "Total: " << totalSum << " RON\n";
//}
//
//int main() {
//    cout << "numar produse: ";
//    cin >> nrProd;
//    cin.get();
//    vector < ConstructionProduct > produse(nrProd);
//    for (auto &produs: produse) {
//        cin >> produs;
//        cin.get();
//    }
//    afisareChitanta(produse);
//    ConstructionProduct produs;
//    cin >> produs;
//    ++produs;
//    produs += 5;
//    cout << produs;
//}

// 3
//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <algorithm>
//
//using std::cin, std::cout, std::ostream, std::istream, std::vector, std::getline, std::string, std::pair, std::abs, std::sort;
//
//
//class InterestPoint {
//    int nrVizitatori, x, y;
//
//public:
//    friend istream &operator>>(istream &is, InterestPoint &interestPoint);
//    friend ostream &operator<<(ostream &os, const InterestPoint &interestPoint);
//
//    InterestPoint(int nrVizitatori, int x, int y);
//    InterestPoint();
//
//    int getNrVizitatori() const;
//
//    void setNrVizitatori(int nrVizitatori);
//
//    int getX() const;
//
//    void setX(int x);
//
//    int getY() const;
//
//    void setY(int y);
//};
//
//int InterestPoint::getNrVizitatori() const {
//    return nrVizitatori;
//}
//
//void InterestPoint::setNrVizitatori(int nrVizitatori) {
//    InterestPoint::nrVizitatori = nrVizitatori;
//}
//
//int InterestPoint::getX() const {
//    return x;
//}
//
//void InterestPoint::setX(int x) {
//    InterestPoint::x = x;
//}
//
//int InterestPoint::getY() const {
//    return y;
//}
//
//void InterestPoint::setY(int y) {
//    InterestPoint::y = y;
//}
//
//InterestPoint::InterestPoint(int nrVizitatori, int x, int y) : nrVizitatori(nrVizitatori), x(x), y(y) {}
//InterestPoint::InterestPoint() {
//    nrVizitatori = x = y = 0;
//}
//
//istream &operator>>(istream &is, InterestPoint &interestPoint) {
//    is >> interestPoint.nrVizitatori >> interestPoint.x >> interestPoint.y;
//    return is;
//}
//
//ostream &operator<<(ostream &os, const InterestPoint &interestPoint) {
//    os << "Vizitatori: " << interestPoint.nrVizitatori << ", x: " << interestPoint.x << ", y: " << interestPoint.y << '\n';
//    return os;
//}
//
//class BikeTrail {
//    string pista, oras;
//    int numberInterestPoints;
//public:
//
//    int getNumberInterestPoints() const;
//
//    void setNumberInterestPoints(int numberInterestPoints);
//
//private:
//    vector < InterestPoint > interestPoints;
//public:
//    friend istream &operator>>(istream &is, BikeTrail &bikeTrail);
//    friend ostream &operator<<(ostream &os, const BikeTrail &bikeTrail);
//
//    BikeTrail(const string &pista, const string &oras, const vector<InterestPoint> &interestPoints);
//    BikeTrail();
//
//    const string &getPista() const;
//
//    void setPista(const string &pista);
//
//    const string &getOras() const;
//
//    void setOras(const string &oras);
//
//    const vector<InterestPoint> &getInterestPoints() const;
//
//    void setInterestPoints(const vector<InterestPoint> &interestPoints);
//};
//
//const string &BikeTrail::getPista() const {
//    return pista;
//}
//
//void BikeTrail::setPista(const string &pista) {
//    BikeTrail::pista = pista;
//}
//
//const string &BikeTrail::getOras() const {
//    return oras;
//}
//
//void BikeTrail::setOras(const string &oras) {
//    BikeTrail::oras = oras;
//}
//
//const vector<InterestPoint> &BikeTrail::getInterestPoints() const {
//    return interestPoints;
//}
//
//void BikeTrail::setInterestPoints(const vector<InterestPoint> &interestPoints) {
//    BikeTrail::interestPoints = interestPoints;
//}
//
//BikeTrail::BikeTrail() {
//    pista = oras = "";
//    interestPoints = {};
//}
//
//BikeTrail::BikeTrail(const string &pista, const string &oras, const vector<InterestPoint> &interestPoints) : pista(
//        pista), oras(oras), interestPoints(interestPoints) {}
//
//istream &operator>>(istream &is, BikeTrail &bikeTrail) {
//    getline(is, bikeTrail.pista);
//    getline(is, bikeTrail.oras);
//    is >> bikeTrail.numberInterestPoints;
//    for (int i = 0; i < bikeTrail.numberInterestPoints; ++i) {
//        InterestPoint tempPoint;
//        cin >> tempPoint;
//        bikeTrail.interestPoints.emplace_back(tempPoint);
//    }
//    return is;
//}
//
//ostream &operator<<(ostream &os, const BikeTrail &bikeTrail) {
//    os << "Pista: " << bikeTrail.pista << ", Oras: " << bikeTrail.oras << '\n';
//    for (const auto &place: bikeTrail.interestPoints) {
//        cout << place;
//    }
//    return os;
//}
//
//int BikeTrail::getNumberInterestPoints() const {
//    return numberInterestPoints;
//}
//
//void BikeTrail::setNumberInterestPoints(int numberInterestPoints) {
//    BikeTrail::numberInterestPoints = numberInterestPoints;
//}
//
//int getDistance2Points(const InterestPoint &point1, const InterestPoint &point2) {
//    return abs(point1.getX() - point2.getX()) + abs(point1.getY() - point2.getY());
//}
//
//void findLongestPath3(const vector < InterestPoint > &points) {
//    int maxLen = 0;
//    int sumViz = 0;
//    vector < InterestPoint > finalPoints(3);
//    int n = points.size();
//    for (int i = 0; i < n; ++i) {
//        InterestPoint point1 = points[i];
//        for (int j = 0; j < n; ++j) {
//            InterestPoint point2 = points[j];
//            for (int k = 0; k < n; ++k) {
//                if (i != j && j != k && i != k) {
//                    InterestPoint point3 = points[k];
//                    int currentLen = getDistance2Points(point1, point2) + getDistance2Points(point2, point3);
//                    if (currentLen > maxLen) {
//                        maxLen = currentLen;
//                        finalPoints = {point1, point2, point3};
//                        sumViz = point1.getNrVizitatori() + point2.getNrVizitatori() + point3.getNrVizitatori();
//                    }
//                }
//            }
//        }
//    }
//    cout << "Lungime maxima: " << maxLen << ", Nr. total vizitatori: " << sumViz << '\n';
//    for (const auto &point: finalPoints) {
//        cout << point;
//    }
//}
//
//bool orderByMostVisited(InterestPoint a, InterestPoint b) {
//    return a.getNrVizitatori() > b.getNrVizitatori();
//}
//
//void minDistance3MostPopular(vector < InterestPoint > points) {
//    int minLen = INT_MAX;
//    vector < InterestPoint > finalPoints(3);
//    sort(points.begin(), points.end(), orderByMostVisited);
//    for (int i = 0; i < 3; ++i) {
//        InterestPoint point1 = points[i];
//        for (int j = 0; j < 3; ++j) {
//            InterestPoint point2 = points[j];
//            for (int k = 0; k < 3; ++k) {
//                if (i != j && j != k && i != k) {
//                    InterestPoint point3 = points[k];
//                    int currentLen = getDistance2Points(point1, point2) + getDistance2Points(point2, point3);
//                    if (currentLen < minLen) {
//                        minLen = currentLen;
//                        finalPoints = {point1, point2, point3};
//                    }
//                }
//            }
//        }
//    }
//    cout << "Distanta minima: " << minLen << '\n';
//    for (int i = 0; i < 3; ++i) {
//        cout << finalPoints[i];
//    }
//}

/*
Traseu#1
Constanta
5
102 0 0
404 10 10
3 1 1
22 3 2
1001 5 0*/

//int main() {
//    BikeTrail bikeTrail;
//    cin >> bikeTrail;
//    cout << bikeTrail;
//    findLongestPath3(bikeTrail.getInterestPoints());
//    minDistance3MostPopular(bikeTrail.getInterestPoints());
//}

// 6
//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <algorithm>
//
//using std::cin, std::cout, std::ostream, std::istream, std::vector, std::getline, std::string, std::pair, std::abs, std::sort;
//
//class Coords {
//    int x, y;
//    int lastValueMatrix;
//public:
//    int getLastValueMatrix() const;
//
//    void setLastValueMatrix(int lastValueMatrix);
//
//public:
//    Coords();
//    Coords(int x, int y, int lastValueMatrix);
//
//    int getX() const;
//
//    void setX(int x);
//
//    int getY() const;
//
//    void setY(int y);
//
//    int getN() const;
//
//    void setN(int n);
//
//    friend istream &operator>>(istream &is, Coords &coords);
//    friend ostream &operator<<(ostream &os, const Coords &coords);
//};
//
//Coords::Coords(int x, int y, int lastValueMatrix = 0) : x(x), y(y), lastValueMatrix(lastValueMatrix) {}
//
//Coords::Coords() {
//    x = y = lastValueMatrix = 0;
//}
//
//istream &operator>>(istream&is, Coords &coords) {
//    is >> coords.x >> coords.y;
//    return is;
//}
//
//ostream &operator<<(ostream &os, const Coords &coords)  {
//    os << "x: " << coords.x << ", y: " << coords.y << ", lastVal: " << coords.lastValueMatrix << '\n';
//    return os;
//}
//
//int Coords::getX() const {
//    return x;
//}
//
//void Coords::setX(int x) {
//    Coords::x = x;
//}
//
//int Coords::getY() const {
//    return y;
//}
//
//void Coords::setY(int y) {
//    Coords::y = y;
//}
//
//int Coords::getLastValueMatrix() const {
//    return lastValueMatrix;
//}
//
//void Coords::setLastValueMatrix(int lastValueMatrix) {
//    Coords::lastValueMatrix = lastValueMatrix;
//}
//
//class Queue {
//    int queueLen;
//    vector < Coords > coords;
//public:
//    Queue();
//    Queue(const vector<Coords>& coords, const int &queueLen);
//
//    int getQueueLen() const;
//
//    void setQueueLen(int queueLen);
//
//    const vector<Coords> &getCoords() const;
//
//    void setCoords(const vector<Coords> &coords);
//
//
//    void clear();
//    bool isEmpty();
//
//    friend istream &operator>>(istream &is, Queue &queue);
//    friend ostream &operator<<(ostream &os, const Queue &queue);
//    friend Queue operator+=(Queue &queue, const Coords &newCoords);
//    friend Queue operator--(Queue &queue);
//
//    Coords operator[](int i) {
//        if (i < this->coords.size()) {
//            return this->coords[i];
//        }
//        else return {-1, -1};
//    }
//};
//
//Queue::Queue(const vector<Coords>& coords, const int &queueLen) : coords(coords), queueLen(queueLen) {}
//Queue::Queue() {
//    coords = {};
//    queueLen = 0;
//}
//
//void Queue::clear() {
//    coords.clear();
//    queueLen = 0;
//}
//
//bool Queue::isEmpty() {
//    return queueLen == 0;
//}
//
//istream &operator>>(istream &is, Queue &queue) {
//    is >> queue.queueLen;
//    for (int i = 0; i < queue.queueLen; ++i) {
//        Coords tempCoords;
//        cin >> tempCoords;
//        queue.coords.emplace_back(tempCoords);
//    }
//    return is;
//}
//
//ostream &operator<<(ostream &os, const Queue &queue) {
//    os << "Length: " << queue.queueLen << '\n';
//    for (int i = 0; i < queue.queueLen; ++i) {
//        cout << queue.coords[i];
//    }
//    return os;
//}
//
//int Queue::getQueueLen() const {
//    return queueLen;
//}
//
//void Queue::setQueueLen(int queueLen) {
//    Queue::queueLen = queueLen;
//}
//
//const vector<Coords> &Queue::getCoords() const {
//    return coords;
//}
//
//void Queue::setCoords(const vector<Coords> &coords) {
//    Queue::coords = coords;
//}
//
//Queue operator+=(Queue &queue, const Coords &newCoords) {
//    queue.coords.emplace_back(newCoords);
//    ++queue.queueLen;
//    return queue;
//}
//
//Queue operator--(Queue &queue) {
//    queue.coords.erase(queue.coords.begin());
//    --queue.queueLen;
//    return queue;
//}
//
//class Maze {
//    vector < vector < int > > matrix{100, vector < int > (100, 0)};
//    int n;
//    Coords start, end;
//    Queue queue;
//
//public:
//    const vector<vector<int>> &getMatrix() const;
//
//    void setMatrix(const vector<vector<int>> &matrix);
//
//    int getN() const;
//
//    void setN(int n);
//
//    const Coords &getStart() const;
//
//    void setStart(const Coords &start);
//
//    const Coords &getAnEnd() const;
//
//    void setAnEnd(const Coords &anEnd);
//
//    const Queue &getQueue() const;
//
//    void setQueue(const Queue &queue);
//
//    Maze();
//    Maze(const vector<vector<int>> &matrix, int n, const Coords &start, const Coords &anEnd, const Queue &queue);
//
//    friend istream &operator>>(istream &is, Maze &maze);
//    friend ostream &operator<<(ostream &os, const Maze &maze);
//};
//
//istream &operator>>(istream &is, Maze &maze) {
//    is >> maze.n;
//    cin >> maze.start >> maze.end;
//    cin >> maze.queue;
//    vector < Coords > tempCoords = maze.queue.getCoords();
//    for (int i = 0; i < maze.queue.getQueueLen(); ++i) {
//        maze.matrix[tempCoords[i].getY()][tempCoords[i].getX()] = -1;
//    }
//    for (int i = 0; i < maze.n; ++i) {
//        for (int j = 0; j < maze.n; ++j) {
//            if (maze.matrix[i][j] != -1) maze.matrix[i][j] = 0;
//        }
//    }
//    return is;
//}
//
//ostream &operator<<(ostream &os, const Maze &maze) {
//    for (int i = 0; i < maze.n; ++i) {
//        for (int j = 0; j < maze.n; ++j) {
//            os << maze.matrix[i][j] << " ";
//        }
//        os << '\n';
//    }
//    return os;
//}
//
//Maze::Maze() {
//    n = 0;
//    start = end = Coords(0, 0);
//    queue = Queue({}, 0);
//}
//
//Maze::Maze(const vector<vector<int>> &matrix, int n, const Coords &start, const Coords &anEnd, const Queue &queue)
//        : matrix(matrix), n(n), start(start), end(anEnd), queue(queue) {}
//
//const vector<vector<int>> &Maze::getMatrix() const {
//    return matrix;
//}
//
//void Maze::setMatrix(const vector<vector<int>> &matrix) {
//    Maze::matrix = matrix;
//}
//
//int Maze::getN() const {
//    return n;
//}
//
//void Maze::setN(int n) {
//    Maze::n = n;
//}
//
//const Coords &Maze::getStart() const {
//    return start;
//}
//
//void Maze::setStart(const Coords &start) {
//    Maze::start = start;
//}
//
//const Coords &Maze::getAnEnd() const {
//    return end;
//}
//
//void Maze::setAnEnd(const Coords &anEnd) {
//    end = anEnd;
//}
//
//const Queue &Maze::getQueue() const {
//    return queue;
//}
//
//void Maze::setQueue(const Queue &queue) {
//    Maze::queue = queue;
//}
//
//void floodFill(Maze &maze, Queue &queue) {
//    Coords firstEl;
//    bool visited[101][101];
//    int smallestDistance = INT_MAX;
//    int nrTimes = 0;
//    for (int i = 0; i < maze.getN(); ++i) {
//        for (int j = 0; j < maze.getN(); ++j) {
//            visited[i][j] = false;
//        }
//    }
//    queue += maze.getStart();
//    while (!queue.isEmpty()) {
//        firstEl = queue[0];
//        --queue;
//        int x = firstEl.getX();
//        int y = firstEl.getY();
//        if (x >= 0 && x < maze.getN() && y >= 0 && y < maze.getN() && maze.getMatrix()[y][x] != -1 && (firstEl.getLastValueMatrix() <= maze.getMatrix()[y][x] || (!visited[y][x] && maze.getMatrix()[y][x] != -1))) {
//            if (firstEl.getX() == maze.getAnEnd().getX() && firstEl.getY() == maze.getAnEnd().getY()) {
//                if (firstEl.getLastValueMatrix() < maze.getMatrix()[y][x] || !maze.getMatrix()[y][x]) {
//                    smallestDistance = firstEl.getLastValueMatrix();
//                    nrTimes = 1;
//                }
//                else if (firstEl.getLastValueMatrix() == maze.getMatrix()[y][x]) ++nrTimes;
//            }
//            visited[y][x] = true;
//            vector < vector < int > > newMatrix = maze.getMatrix();
//            newMatrix[y][x] = firstEl.getLastValueMatrix();
//            int lastVal = firstEl.getLastValueMatrix() + 1;
//            maze.setMatrix(newMatrix);
//            queue += Coords(x, y - 1, lastVal);
//            queue += Coords(x - 1, y, lastVal);
//            queue += Coords(x, y + 1, lastVal);
//            queue += Coords(x + 1, y, lastVal);
//        }
//    }
//    cout << maze;
//    cout << "============" << '\n';
//    cout << "Distanta minima: " << smallestDistance << '\n';
//    cout << "Numar drumuri: " << nrTimes << '\n';
//}
//
//// 5 0 0 4 0 5 1 0 1 2 2 2 3 2 4 1
//int main() {
//    Maze maze;
//    Queue queue;
//    cin >> maze;
//    floodFill(maze, queue);
//}