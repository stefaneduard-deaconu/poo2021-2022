// 1. Spalatorie automata
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::make_pair;

class Durata {
private:
  int minute, secunde;

public:
  Durata() {
    minute = secunde = 0;
  }

  Durata(int _minute, int _secunde) {
    minute = _minute;
    secunde = _secunde;
  }

  pair < int, int > getTime();
};

pair < int, int > Durata::getTime() {
    return {minute, secunde};
}

class MasinaSpalat {
private:
  bool isFree;
  Durata timeLeft;
  int capsule;

public:
  MasinaSpalat() {
    isFree = capsule = 0;
    timeLeft = Durata(0, 0);
  }

  MasinaSpalat(bool _isFree, Durata _timeLeft, int _capsule) {
    isFree = _isFree;
    timeLeft = _timeLeft;
    capsule = _capsule;
  }

  bool getFree() const;
  int getCapsule() const;
  void setCapsule(int _capsule);
  void decrementCapsule();
  void setDurata(Durata _timeLeft);
  Durata getDurata();
  void setFree(bool _isFree);
};

bool MasinaSpalat::getFree() const {
  return isFree;
}

int MasinaSpalat::getCapsule() const {
  return capsule;
}

void MasinaSpalat::setCapsule(int _capsule) {
  capsule = _capsule;
}

void MasinaSpalat::decrementCapsule() {
  capsule -= 1;
}

void MasinaSpalat::setDurata(Durata _timeLeft) {
  timeLeft = _timeLeft;
}

Durata MasinaSpalat::getDurata() {
  return timeLeft;
}

void MasinaSpalat::setFree(bool _isFree) {
  isFree = _isFree;
}

class Spalatorie {
private:
  int nrMasini;
  vector < MasinaSpalat > masini;

public:
  Spalatorie() {
    nrMasini = 0;
    masini = {};
  }

  Spalatorie(int _nrMasini, vector < MasinaSpalat > _masini) {
    nrMasini = _nrMasini;
    masini = _masini;
  }

  void listeazaMasini();
  vector < MasinaSpalat > getMasini();
  void adaugaJob(int index, Durata timp);
  void actualizeazaTimp(Durata _timp);
};

void Spalatorie::listeazaMasini() {
  cout << "Spalatoria in prezent:\n";
  for (int i = 0; i < nrMasini; ++i) {
    cout << i << ". ";
    pair < int, int > time = masini[i].getDurata().getTime();
    if (!time.first && !time.second) masini[i].setFree(true);
    if (!masini[i].getCapsule()) cout << "Masina este neutilizabila! Nu mai are capsule!\n";
    else if (masini[i].getFree()) {
      cout << "Masina este libera.\n";
    }
    else { 
      cout << "Masina este ocupata pentru inca " << time.first << ":";
      if (time.second < 10) cout << "0" << time.second << '\n';
      else cout << time.second << '\n';
    }
    
  }
}

void Spalatorie::adaugaJob(int index, Durata timp) {
  auto it = masini.begin() + index;
  if (!(*it).getCapsule()) {
    cout << "Masina " << index << " nu mai are capsule!\n";
  }
  else {
    (*it).decrementCapsule();
    (*it).setDurata(timp);
    (*it).setFree(false);
  }
}

vector < MasinaSpalat > Spalatorie::getMasini() {
  return masini;
}

void Spalatorie::actualizeazaTimp(Durata _timp) {
  for (auto & masina : masini) {
    int min = masina.getDurata().getTime().first;
    int sec = masina.getDurata().getTime().second;
    int actualMin = _timp.getTime().first;
    int actualSec = _timp.getTime().second;
    if (actualMin > min || (actualMin == min && actualSec >= sec)) {
      min = sec = 0;
    }
    else {
      if (actualMin < min) {
        min -= 1;
        sec += 60;
      }
      min -= actualMin;
      sec -= actualSec;
    }
    masina.setDurata(Durata(min, sec));
  }
}

void listeazaMasiniLibere(Spalatorie spalatorie) {
  vector < int > indexMasiniLibere;
  vector < MasinaSpalat > masini = spalatorie.getMasini();
  for (auto it = masini.begin(); it != masini.end(); ++it) {
    if ((*it).getFree()) {
      indexMasiniLibere.emplace_back(it - masini.begin());
    }
  }
  if (indexMasiniLibere.empty()) cout << "Nu exista masini de spalat libere.\n";
  else {
    cout << "Urmatoarele masini sunt libere : ";
    for (auto & index : indexMasiniLibere) {
      cout << index << " ";
    }
    cout << '\n';
  }
}

int main() {
  vector < MasinaSpalat > masini = {
    MasinaSpalat(true, Durata(0, 0), 3),
    MasinaSpalat(true, Durata(0, 0), 2),
    MasinaSpalat(true, Durata(0, 0), 5)
  };

//  auto& masina1 = masini[0];
//  cout << masina1.getCapsule() << '\n';
//   masina1.setCapsule(7);
//  cout << masina1.getCapsule() << '\n';
//  cout << masini[0].getCapsule() << '\n';
//  return 0;

  Spalatorie spalatorie(3, masini);
  spalatorie.listeazaMasini();
  listeazaMasiniLibere(spalatorie);

  spalatorie.adaugaJob(1, Durata(1, 20));

  spalatorie.listeazaMasini();

  spalatorie.actualizeazaTimp(Durata(1, 19));
  spalatorie.listeazaMasini();

  spalatorie.actualizeazaTimp(Durata(1, 0));
  spalatorie.listeazaMasini();

  spalatorie.adaugaJob(1, Durata(0, 35));
  spalatorie.actualizeazaTimp(Durata(3, 0));
  
  spalatorie.adaugaJob(1, Durata(0, 35));
  spalatorie.listeazaMasini();
  return 0;
}