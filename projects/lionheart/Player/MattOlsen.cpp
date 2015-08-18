#include "MattOlsen.hpp"
#include "SituationReport.hpp"

lionheart::Placement lionheart::MattOlsen::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
    ++id;
    westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));
    if(westSide)
    {
        switch(id)
        {
                // CROWN
            case 1: return {14, 4};
                // KNIGHTS
            case 2: return {10,3};
            case 3: return {10,5};
            case 4: return {13,7};
            case 5: return {16,7};
            case 6: return {19,3};
            case 7: return {19,5};
                // ARCHERS
            case 8: return {11,4};
            case 9: return {12,4};
            case 10:return {14,3};
            case 11:return {15,3};
            case 12:return {14,6};
            case 13:return {15,6};
            case 14: return {17,4};
            case 15: return {18,4};
                // INFANTRY
            case 16: return {10,4};
            case 17: return {12,3};
            case 18: return {12,5};
            case 19: return {13,4};
            case 20: return {13,5};
            case 21: return {14,5};
            case 22: return {14,7};
            case 23: return {15,4};
            case 24: return {15,5};
            case 25: return {15,7};
            case 26: return {16,4};
            case 27: return {16,5};
            case 28: return {17,3};
            case 29: return {17,5};
            case 30: return {19,4};
        }
    }
    else
    {
        switch (id)
        {
                // CROWN
            case 1: return {14,25};
                // KNIGHTS
            case 2: return {10,24};
            case 3: return {10,26};
            case 4: return {13,22};
            case 5: return {16,22};
            case 6: return {19,24};
            case 7: return {19,26};
                // ARCHERS
            case 8: return {11,25};
            case 9: return {12,25};
            case 10:return {14,23};
            case 11:return {14,26};
            case 12:return {15,23};
            case 13:return {15,26};
            case 14: return {17,25};
            case 15: return {18,25};
                // INFANTRY
            case 16: return {10,25};
            case 17: return {12,26};
            case 18: return {12,24};
            case 19: return {13,25};
            case 20: return {13,24};
            case 21: return {14,24};
            case 22: return {14,22};
            case 23: return {15,25};
            case 24: return {15,24};
            case 25: return {15,22};
            case 26: return {16,25};
            case 27: return {16,24};
            case 28: return {17,26};
            case 29: return {17,24};
            case 30: return {19,25};
        }
    }
    return {0,0};
}

lionheart::Action
lionheart::MattOlsen::recommendAction(Unit const& u, SituationReport report, Plan p)
{
    if(report.turns <= 20)
    {
        if(westSide)
        {
            if(p.hasAttack()) return p.attackEnemy();
            switch(u.getId())
                {
                    case 0: return wait();
                        // KNIGHTS
                    case 1: return turn(Direction::EAST);
                    case 2: return turn(Direction::WEST);
                    case 3: return turn(Direction::SOUTH);
                    case 4: return turn(Direction::NORTH);
                    case 5: return turn(Direction::EAST);
                    case 6: return turn(Direction::WEST);
                        // ARCHERS
                    case 7: case 8: return turn(Direction::NORTH);
                    case 9: case 10: return turn(Direction::WEST);
                    case 11: case 12: return turn(Direction::EAST);
                    case 13: case 14: return turn(Direction::SOUTH);
                        // INFANTRY
                    case 15: return turn(Direction::NORTH);
                    case 16: return turn(Direction::EAST);
                    case 17: return turn(Direction::WEST);
                    case 18: return turn(Direction::NORTH);
                    case 19: return turn(Direction::SOUTH);
                    case 20: return turn(Direction::EAST);
                    case 21: return turn(Direction::EAST);
                    case 22: return turn(Direction::EAST);
                    case 23: return turn(Direction::EAST);
                    case 24: return turn(Direction::EAST);
                    case 25: return turn(Direction::SOUTH);
                    case 26: return turn(Direction::NORTH);
                    case 27: return turn(Direction::EAST);
                    case 28: return turn(Direction::WEST);
                    case 29: return turn(Direction::SOUTH);
                }
        }
        else
        {
            if(p.hasAttack()) return p.attackEnemy();
            switch(u.getId())
                {
                    case 0: return wait();
                        // KNIGHTS
                    case 1: return turn(Direction::EAST);
                    case 2: return turn(Direction::WEST);
                    case 3: return turn(Direction::SOUTH);
                    case 4: return turn(Direction::NORTH);
                    case 5: return turn(Direction::EAST);
                    case 6: return turn(Direction::WEST);
                        // ARCHERS
                    case 7: case 8: return turn(Direction::NORTH);
                    case 9: case 10: return turn(Direction::WEST);
                    case 11: case 12: return turn(Direction::EAST);
                    case 13: case 14: return turn(Direction::SOUTH);
                        // INFANTRY
                    case 15: return turn(Direction::NORTH);
                    case 16: return turn(Direction::EAST);
                    case 17: return turn(Direction::WEST);
                    case 18: return turn(Direction::NORTH);
                    case 19: return turn(Direction::SOUTH);
                    case 20: return turn(Direction::WEST);
                    case 21: return turn(Direction::WEST);
                    case 22: return turn(Direction::WEST);
                    case 23: return turn(Direction::WEST);
                    case 25: return turn(Direction::SOUTH);
                    case 26: return turn(Direction::NORTH);
                    case 27: return turn(Direction::EAST);
                    case 28: return turn(Direction::WEST);
                    case 29: return turn(Direction::SOUTH);
                }
        }
    }

    if(report.turns > 20)
    {
        if (u.getType() == CROWN)
        {
            return wait();
        }
        if((u.getType() == KNIGHT)||(u.getType() == INFANTRY))
        {
            if(p.hasAttack())
            {
                return p.attackEnemy();
            }
            return p.moveToEnemyCrown();
        }
        if(u.getType() == ARCHER)
        {
            if(westSide)
            {
                if (p.movesToEnemy() < 4)
                {
                    return p.attackEnemy();
                }
                if (p.movesToEnemy() > 4)
                    switch(u.getId())
                    {
                        case 7: return p.moveToLocation(12,4);
                        case 8: return p.moveToLocation(13,4);
                        case 9: return p.moveToLocation(14,3);
                        case 10: return p.moveToLocation(15,3);
                        case 11: return p.moveToLocation(14,5);
                        case 12: return p.moveToLocation(15,5);
                        case 13: return p.moveToLocation(15,4);
                        case 14: return p.moveToLocation(16,4);
                    }
            }
            else
            {
                if (p.movesToEnemy() < 4)
                {
                    return p.attackEnemy();
                }
                if (p.movesToEnemy() > 4)
                    switch(u.getId())
                    {
                        case 7: return p.moveToLocation(12,25);
                        case 8: return p.moveToLocation(13,25);
                        case 9: return p.moveToLocation(14,24);
                        case 10: return p.moveToLocation(15,24);
                        case 11: return p.moveToLocation(14,26);
                        case 12: return p.moveToLocation(15,26);
                        case 13: return p.moveToLocation(15,25);
                        case 14: return p.moveToLocation(16,25);
                    }
            }
        }
    }
    return p.attackEnemy();
}

lionheart::Blazon lionheart::MattOlsen::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
    {return {Color::ARGENT, Color::AZURE, Style::CROSS, "Brotherhood Of Steel"};}
}
