class GameEntity {
public:
    virtual void interact(Player& player) = 0;
    virtual ~GameEntity() {}
    virtual std::string describe() const = 0;
};


class Player {
    int sanity;
    bool riverStones[3];
    bool monsterDefeated[3];
    Node* currentLocation;

public:
    Player() : sanity(10), currentLocation(nullptr) {
        std::fill(std::begin(riverStones), std::end(riverStones), false);
        std::fill(std::begin(monsterDefeated), std::end(monsterDefeated), false);
    }

    void move(Node* location) {
        if (location != currentLocation) {
            currentLocation = location;
            sanity--;
            if (sanity <= 0) {
                std::cout << "Overwhelmed by the fog, you lose all sense of direction and hope...\n";
                exit(0);
            }
        }
    }

    void rest() {
        sanity++;
        if (rand() % 100 < 15) {
            std::cout << "The fog creeps closer, chilling your bones and clouding your mind...\n";
            sanity--;
        }
    }

    void collectRiverStone(int id) {

      
    }

    bool hasRiverStone(int id) const {
        return id >= 0 && id < 3 && riverStones[id];
    }

    void collectRiverStone(int id) {
        if (id >= 0 && id < 3) {
            riverStones[id] = true;
            std::cout << "You've found a stone to calm the waters of River " << id + 1 << ".\n";
        }
    }

    void encounterMonster(int id) {
        if (id >= 0 && id < 3 && !monsterDefeated[id]) {
            if (rand() % 100 < 50) {
                std::cout << "The monster terrorizes you for your weakness, draining your sanity...\n";
                sanity -= 2;
            }
            else if (rand() % 100 < 25) {
                collectRiverStone(id);
            }
            monsterDefeated[id] = true;
        }
    }

    void defeatMonster(int id) {

       
    }

    bool isMonsterDefeated(int id) const {
        
    }

    GameEntity* getCurrentLocation() const {
        return currentLocation->entity.get();
    }

    int getSanity() const {
        return sanity;
    }

    void menu();


    bool hasRiverStone(int id) const {
        return id >= 0 && id < 3 && riverStones[id];
    }
};



// Definitions for different types of spaces
class Monster : public GameEntity {
    std::string name;
    int winProbability;
    int monsterId;
    bool defeated;

public:
    Monster(const std::string& name, int winProb, int id) : name(name), winProbability(winProb), monsterId(id), defeated(false) {}

    void interact(Player& player) override {
        std::cout << "You encounter " << name << ". Roll a die to determine your fate.\n";
        int result = rand() % 100;
        if (result < winProbability) {
            std::cout << "You've defeated " << name << " and calm the nearby river.\n";
            player.defeatMonster(monsterId);
            defeated = true;
        }
        else {
            std::cout << "You failed to defeat " << name << " and lose 1 sanity point.\n";
            player.sanity--;
        }
    }

    std::string describe() const override {
        return "Monster " + name + " blocks your path.";
    }
};


class RiverSpace : public GameEntity {

    int riverId;
    bool unlocked1, unlocked2, unlocked3;

public:
    RiverSpace(int id) : riverId(id), unlocked(false) {}

    void interact(Player& player) override {



        if (player.hasRiverStone() <= 1) {
            std::cout << "The river is calm, you can cross safely.\n";
        }
        if (riverId == 0) {
            if (player.hasRiverStone() <= 1) {
                std::cout << "The river is calm, you can cross safely.\n";
            }
            else {
                //go to node registry space 1
            }
        }
		if (riverId == 1) {
			if (player.hasRiverStone() <= 2) {
				std::cout << "The river is calm, you can cross safely.\n";
			}
			else {
				//go to node registry space 1
			}
		}
		if (riverId == 2) {
			if (player.hasRiverStone() <= 3) {
				std::cout << "The river is calm, you can cross safely.\n";
			}
			else {
				//go to node registry space 1
			}
		}




    }

};


class FogSpace : public GameEntity {


}
