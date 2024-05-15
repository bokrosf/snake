#include <game/game_event.h>
#include <game/snake/snake.h>
#include <game/wall/wall.h>

wall::wall(entity &attached_to, const vector2 &area)
    : behavior(attached_to)
    , _area(area)
{
}

const vector2 &wall::area() const
{
    return _area;
}

void wall::collide(const collision &collision)
{
    if (collision.collider.attached_to().find_component<snake>())
    {
        _messenger.send(game_event::game_lost);
    }
}
