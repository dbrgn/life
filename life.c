/**
 * A simple game of life implementation written in C using Clutter.
 * Copyright (C) 2013 Danilo Bargen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <clutter/clutter.h>

#define FIELD_WIDTH 20
#define FIELDS_PER_SIDE 20
#define BOTTOM_HEIGHT 40

ClutterActor* fields[FIELDS_PER_SIDE][FIELDS_PER_SIDE];

ClutterColor stage_color = { 0, 64, 0, 255 };
ClutterColor lgreen = { 0, 255, 0, 192 };
ClutterColor dgreen = { 0, 223, 0, 160 };
ClutterColor white = { 255, 255, 255, 192 };
ClutterColor black = { 0, 0, 0, 192 };

gint generation = 0;

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

void on_step_button_press(ClutterActor *actor, ClutterEvent *event, gpointer data) {
    g_print("Generation %u\n", ++generation);
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
            fields[i][j] = rect;
            clutter_actor_set_size(rect, FIELD_WIDTH, FIELD_WIDTH);
            clutter_actor_set_position(rect, i * FIELD_WIDTH, j * FIELD_WIDTH);
            clutter_actor_set_reactive(rect, TRUE);
            clutter_rectangle_set_color(CLUTTER_RECTANGLE(rect), &stage_color);
            clutter_rectangle_set_border_width(CLUTTER_RECTANGLE(rect), 1);
            clutter_rectangle_set_border_color(CLUTTER_RECTANGLE(rect), &dgreen);
            clutter_container_add_actor(CLUTTER_CONTAINER(stage), rect);
            g_signal_connect(rect, "button-press-event", G_CALLBACK(on_rect_button_press), NULL);
            clutter_actor_show(rect);
        }
    }

    // Create button
    ClutterActor *button = clutter_rectangle_new();
    gint button_width = FIELD_WIDTH * FIELDS_PER_SIDE / 4;
    gint button_height = BOTTOM_HEIGHT / 2;
    clutter_actor_set_size(button, button_width, button_height);
    clutter_actor_set_position(button, FIELD_WIDTH * FIELDS_PER_SIDE / 2, FIELD_WIDTH * FIELDS_PER_SIDE + BOTTOM_HEIGHT / 2);
    clutter_actor_set_anchor_point(button, button_width / 2, button_height / 2);
    clutter_actor_set_reactive(button, TRUE);
    clutter_rectangle_set_color(CLUTTER_RECTANGLE(button), &lgreen);
    clutter_rectangle_set_border_width(CLUTTER_RECTANGLE(button), 2);
    clutter_rectangle_set_border_color(CLUTTER_RECTANGLE(button), &dgreen);
    clutter_container_add_actor(CLUTTER_CONTAINER(stage), button);
    g_signal_connect(button, "button-press-event", G_CALLBACK(on_step_button_press), NULL);
    clutter_actor_show(button);

    // Create button text
    ClutterActor *buttontext = clutter_text_new();
    clutter_actor_set_position(buttontext, FIELD_WIDTH * FIELDS_PER_SIDE / 2 - button_width / 2 + 30, FIELD_WIDTH * FIELDS_PER_SIDE + BOTTOM_HEIGHT / 4 + 1);
    clutter_actor_set_size(buttontext, button_width, button_height);
    clutter_text_set_text(CLUTTER_TEXT(buttontext), "Step");
    clutter_text_set_color(CLUTTER_TEXT(buttontext), &stage_color);
    clutter_text_set_font_name(CLUTTER_TEXT(buttontext), "15px");
    clutter_container_add_actor(CLUTTER_CONTAINER(stage), buttontext);
    clutter_actor_show(buttontext);

    // Show stage
    clutter_actor_show(stage);

    // Main event loop
    clutter_main();

    return EXIT_SUCCESS;
}
