#include <cairo.h>
#include <stdio.h>

// Définir les poids et les biais
typedef struct {
    char *nom;
    double poids;
} Connexion;

typedef struct {
    char *nom;
    double biais;
} Neurone;

// Définir les poids pour les connexions
Connexion connexions[] = {
    {"input_0_to_hidden_0", 0.1115},
    {"input_0_to_hidden_1", -6.1446},
    {"input_1_to_hidden_0", -6.1740},
    {"input_1_to_hidden_1", 0.2037},
    {"hidden_0_to_output_0", -7.4508},
    {"hidden_1_to_output_0", -7.6396}
};

// Définir les biais pour les neurones
Neurone neurones[] = {
    {"input_0", 0},
    {"input_1", 0},
    {"hidden_0", 0.8200},
    {"hidden_1", 0.6700},
    {"output_0", 0.8200}
};

void dessiner_reseau(cairo_t *cr) {
    // Positions des neurones dans le réseau
    double pos_input[2] = {100, 300};
    double pos_hidden_0[2] = {300, 400};
    double pos_hidden_1[2] = {300, 200};
    double pos_output[2] = {500, 300};

    // Dessiner les neurones
    cairo_arc(cr, pos_input[0], pos_input[1], 20, 0, 2 * 3.14);
    cairo_fill(cr);
    cairo_move_to(cr, pos_input[0] - 10, pos_input[1] + 5);
    cairo_show_text(cr, "input_0");

    cairo_arc(cr, pos_input[0], pos_input[1] - 100, 20, 0, 2 * 3.14);
    cairo_fill(cr);
    cairo_move_to(cr, pos_input[0] - 10, pos_input[1] - 95);
    cairo_show_text(cr, "input_1");

    cairo_arc(cr, pos_hidden_0[0], pos_hidden_0[1], 20, 0, 2 * 3.14);
    cairo_fill(cr);
    cairo_move_to(cr, pos_hidden_0[0] - 10, pos_hidden_0[1] + 5);
    cairo_show_text(cr, "hidden_0");

    cairo_arc(cr, pos_hidden_1[0], pos_hidden_1[1], 20, 0, 2 * 3.14);
    cairo_fill(cr);
    cairo_move_to(cr, pos_hidden_1[0] - 10, pos_hidden_1[1] + 5);
    cairo_show_text(cr, "hidden_1");

    cairo_arc(cr, pos_output[0], pos_output[1], 20, 0, 2 * 3.14);
    cairo_fill(cr);
    cairo_move_to(cr, pos_output[0] - 10, pos_output[1] + 5);
    cairo_show_text(cr, "output_0");

    // Dessiner les connexions entre les neurones
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, pos_input[0], pos_input[1]);
    cairo_line_to(cr, pos_hidden_0[0], pos_hidden_0[1]);
    cairo_move_to(cr, pos_input[0], pos_input[1] - 100);
    cairo_line_to(cr, pos_hidden_1[0], pos_hidden_1[1]);
    cairo_move_to(cr, pos_hidden_0[0], pos_hidden_0[1]);
    cairo_line_to(cr, pos_output[0], pos_output[1]);
    cairo_move_to(cr, pos_hidden_1[0], pos_hidden_1[1]);
    cairo_line_to(cr, pos_output[0], pos_output[1]);
    cairo_stroke(cr);

    // Afficher les poids sur les arêtes
    cairo_move_to(cr, (pos_input[0] + pos_hidden_0[0]) / 2, (pos_input[1] + pos_hidden_0[1]) / 2);
    cairo_show_text(cr, "Poids: 0.1115");

    cairo_move_to(cr, (pos_input[0] + pos_hidden_1[0]) / 2, (pos_input[1] - 100 + pos_hidden_1[1]) / 2);
    cairo_show_text(cr, "Poids: -6.1446");

    cairo_move_to(cr, (pos_input[0] + pos_hidden_0[0]) / 2, (pos_input[1] + pos_hidden_0[1]) / 2);
    cairo_show_text(cr, "Poids: -6.1740");

    cairo_move_to(cr, (pos_hidden_0[0] + pos_output[0]) / 2, (pos_hidden_0[1] + pos_output[1]) / 2);
    cairo_show_text(cr, "Poids: -7.4508");

    cairo_move_to(cr, (pos_hidden_1[0] + pos_output[0]) / 2, (pos_hidden_1[1] + pos_output[1]) / 2);
    cairo_show_text(cr, "Poids: -7.6396");

    // Afficher les biais près des neurones
    cairo_move_to(cr, pos_hidden_0[0] - 20, pos_hidden_0[1] + 25);
    cairo_show_text(cr, "Biais: 0.8200");

    cairo_move_to(cr, pos_hidden_1[0] - 20, pos_hidden_1[1] + 25);
    cairo_show_text(cr, "Biais: 0.6700");

    cairo_move_to(cr, pos_output[0] - 20, pos_output[1] + 25);
    cairo_show_text(cr, "Biais: 0.8200");
}

int main() {
    // Créer une surface d'image avec Cairo
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 600, 400);
    cairo_t *cr = cairo_create(surface);

    // Dessiner le réseau
    dessiner_reseau(cr);

    // Sauver l'image dans un fichier
    cairo_surface_write_to_png(surface, "reseau_neurones.png");

    // Libérer la mémoire
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    printf("Le graphique a été généré et sauvegardé sous 'reseau_neurones.png'.\n");

    return 0;
}
