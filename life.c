#include <stdlib.h>
#include <clutter/clutter.h>

#define FIELD_WIDTH 20
#define FIELDS_PER_SIDE 20
#define BOTTOM_HEIGHT 40

ClutterActor* fields[FIELDS_PER_SIDE][FIELDS_PER_SIDE];

ClutterColor stage_color = { 0, 64, 0, 255 };
ClutterColor lgreen = { 0, 255, 0, 192 };
ClutterColor dgreen = { 0, 223, 0, 160 };

void on_rect_button_press(ClutterActor *actor, ClutterEvent *event, gpointer data) {
    ClutterColor oldcolor, newcolor;
    clutter_rectangle_get_color(CLUTTER_RECTANGLE(actor), &oldcolor);
    if (clutter_color_equal(&oldcolor, &stage_color)) {
        newcolor = lgreen;
    } else {
        newcolor = stage_color;
    }
    clutter_rectangle_set_color(CLUTTER_RECTANGLE(actor), &newcolor);
}

int main(int argc, char *argv[]) {
    clutter_init(&argc, &argv);


    // Set up stage
    ClutterActor *stage = clutter_stage_new();
    clutter_actor_set_size(stage, FIELD_WIDTH * FIELDS_PER_SIDE, FIELD_WIDTH * FIELDS_PER_SIDE + BOTTOM_HEIGHT);
    clutter_actor_set_background_color(stage, &stage_color);
    clutter_stage_set_title(CLUTTER_STAGE(stage), "Game Of Life");

    // Create rectangles
    for (int i = 0; i < FIELDS_PER_SIDE; i++) {
        for (int j = 0; j < FIELDS_PER_SIDE; j++) {
            ClutterActor *rect = clutter_rectangle_new();
            clutter_actor_set_size(rect, FIELD_WIDTH, FIELD_WIDTH);
            clutter_actor_set_position(rect, i * FIELD_WIDTH, j * FIELD_WIDTH);
            clutter_actor_set_reactive(rect, TRUE);
            clutter_rectangle_set_color(CLUTTER_RECTANGLE(rect), &stage_color);
            clutter_rectangle_set_border_width(CLUTTER_RECTANGLE(rect), 1);
            clutter_rectangle_set_border_color(CLUTTER_RECTANGLE(rect), &dgreen);
            clutter_container_add_actor(CLUTTER_CONTAINER(stage), rect);
            clutter_actor_show(rect);
            fields[i][j] = rect;

            // Attach click handlers
            g_signal_connect(rect, "button-press-event", G_CALLBACK(on_rect_button_press), NULL);
        }
    }

    // Show stage
    clutter_actor_show(stage);

    // Main event loop
    clutter_main();

    return EXIT_SUCCESS;
}
