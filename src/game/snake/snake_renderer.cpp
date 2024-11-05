#include <engine/entity.h>
#include <game/color.h>
#include <game/entity_name.h>
#include <game/snake/snake_renderer.h>

snake_renderer::snake_renderer()
    : _snake(nullptr)
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
    
    render_body(renderer);
    render_head(renderer);
}

void snake_renderer::render_body(SDL_Renderer *renderer)
{
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

void snake_renderer::render_head(SDL_Renderer *renderer)
{
    use_color(renderer, color::snake_head);
    const snake::segment &head = *_snake->segments().begin();
    vector2 begin = _maze->tile_center(head.begin.y, head.begin.x);
    vector2 end = _maze->tile_center(head.end.y, head.end.x);

    vector2 head_direction = end.square_distance_from(begin) > 0
        ? end.points_to(begin).normalize()
        : vector2::left();

    vector2 thickness_direction = head_direction.orthogonal();
    vector2 area = 0.15F * thickness() * head_direction
        + 0.15F * thickness() * thickness_direction;

    vector2 position = begin
        + 0.25F * thickness() * head_direction
        + area
        + 0.5F * thickness() * thickness_direction;

    SDL_FRect eye
    {
        .x = position.x,
        .y = position.y,
        .w = -2.0F * area.x,
        .h = -2.0F * area.y
    };

    SDL_RenderFillRectF(renderer, &eye);

    position = begin
        + 0.25F * thickness() * head_direction
        + area
        - 0.5F * thickness() * thickness_direction;

    eye.x = position.x;
    eye.y = position.y;
    SDL_RenderFillRectF(renderer, &eye);

    area = 0.5F * thickness() * head_direction + 0.4F * thickness() * thickness_direction;
    area *= 0.5F;
    position = begin + area + thickness() * head_direction;

    SDL_FRect tounge
    {
        .x = position.x,
        .y = position.y,
        .w = -2.0F * area.x,
        .h = -2.0F * area.y
    };

    SDL_RenderFillRectF(renderer, &tounge);
}

int snake_renderer::thickness() const
{
    return 0.25F * _maze->tile_size();
}
