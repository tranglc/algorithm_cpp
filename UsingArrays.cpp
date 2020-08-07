#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;

class IndexOutOfBounds : public exception
{
private:
    string _msg;
public:
    IndexOutOfBounds(const string& msg) :
        _msg(msg) {

    }
    const char* what() const noexcept {
        return _msg.c_str();
    }
};
class GameEntry
{
public:
    GameEntry(const string& n="", int s = 0);
    string getName()const;
    int getScore() const;
private:
    string name;
    int score;
};

GameEntry::GameEntry(const string& _name, int _score)
    :name(_name), score(_score) {}
string GameEntry::getName() const
{
    return name;
}
int GameEntry::getScore() const
{
    return score;
}

class Scores
{
public:
    Scores(int maxEnt = 10);
    ~Scores() {};
    void add(const GameEntry& entry);
    void printAll() const;
    void insertionSort();
    void selectionSort();
    GameEntry remove(int i)
        throw(IndexOutOfBounds);
private:
    int maxEntries;
    int numEntries;
    unique_ptr<GameEntry[]> entries;
};
Scores::Scores(int maxEnt)
{
    maxEntries = maxEnt;
    entries = make_unique<GameEntry[]>(maxEntries);
    numEntries = 0;
}
void Scores::add(const GameEntry& entry)
{
    int newScore = entry.getScore();
    if (numEntries == maxEntries) {
        if (newScore <= entries[maxEntries-1].getScore())
            return;
    }
    else {
        numEntries++;
    }
    int i = numEntries -2;
    while (i >= 0 && newScore > entries[i].getScore()) {
        entries[i+1] = entries[i];
        i--;
    }
    entries[i+1] = entry;
}

GameEntry Scores::remove(int i) throw(IndexOutOfBounds) {
    if ((i<0) || (i >= numEntries))
        throw IndexOutOfBounds("Invalid index");
    GameEntry _save = entries[i];
    while (i < (numEntries -1))
    {
        entries[i] = entries[i+1];
        i++;
    }
    numEntries--;
    return _save;
}

void Scores::printAll() const {
    for (int i = 0; i < numEntries; i++) {
        cout <<"("<<entries[i].getName()<<", "<<entries[i].getScore()<<") ";
    }
    cout << endl;
}
void Scores::insertionSort() {
    int j = 0;
    for (int i = 1; i < numEntries; i++) {
        j = i -1;
        while (j >= 0 && (entries[j+1].getScore()<entries[j].getScore()))
        {
            swap(entries[j+1], entries[j]);
            j--;
        }
    }
}
void Scores::selectionSort() {
    int indexOfMin = 0;
    for (int i = 0; i < numEntries -1; i++) {
        indexOfMin = i;
        for (int j = i; j < numEntries - 1; j++){
            if (entries[j+1].getScore() < entries[j].getScore())
            {
                indexOfMin = j+1;
            }
        }
        if(indexOfMin != i){
            swap(entries[i],entries[indexOfMin]);
        }
    }
}

int main()
{
    Scores m_scores;
    GameEntry entries[6] ={ { "Mike", 1105 }, { "Rob", 750 },
        { "Jill", 740 }, { "Anna", 660 }, { "Rose", 590 }, { "Jack", 510 } };
    m_scores.add(entries[0]);
    m_scores.add(entries[1]);
    m_scores.add(entries[2]);
    m_scores.add(entries[3]);
    m_scores.add(entries[4]);
    m_scores.add(entries[5]);
    m_scores.printAll();
    m_scores.remove(1);
    m_scores.printAll();
    m_scores.add(GameEntry("John", 900));
    m_scores.selectionSort();
    m_scores.printAll();
    return 0;

}