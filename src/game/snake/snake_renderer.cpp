#include <game/entity_name.h>
#include <game/snake/snake_renderer.h>

snake_renderer::snake_renderer(entity& attached_to, int layer_order)
    : renderer(attached_to, layer_order)
    , _snake(nullptr)
    , _maze(nullptr)
{
}

void snake_renderer::initialize()
{
    _snake = &attached_to().attached_component<snake>();
    _maze = &attached_to().find(entity_name::map)->attached_component<tile_maze>();
}

void snake_renderer::render(SDL_Renderer *renderer)
{    
    if (!use_material_color(renderer))
    {
        return;
    }
    
    for (const auto &segment : _snake->segments())
    {
        vector2 begin = _maze->tile_center(segment.begin.y, segment.begin.x);
        vector2 end = _maze->tile_center(segment.end.y, segment.end.x);
        
        vector2 direction = begin.square_distance_from(end) > 0
            ? begin.points_to(end).normalize()
            : vector2::left();

        vector2 corner_offset = thickness() * (direction + direction.orthogonal());
        begin -= corner_offset;
        end += corner_offset;
        vector2 area = begin.points_to(end);

        SDL_FRect body_part
        {
            .x = begin.x,
            .y = begin.y,
            .w = area.x,
            .h = area.y
        };

        SDL_RenderFillRectF(renderer, &body_part);
    }
}

int snake_renderer::thickness() const
{
    return 0.25F * _maze->tile_size();
}
