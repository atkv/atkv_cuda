/**
 ** This file is part of the atkv project.
 ** Copyright 2016 Anderson Tavares <nocturne.pe@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <at/gui.h>
static void
activate(GtkApplication* app, gpointer user_data){
  AtError      * error = NULL;
  AtArrayU8    * image = at_arrayu8_read_png("teste.png",&error);
  AtImageWindow* window= NULL;
  if(error)
    fprintf(stderr, "%s", error->message);
  else{
    window = at_imagewindow_new();
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_widget_show_all(GTK_WIDGET(window));
    at_imagewindow_set(window, image);
    gtk_main();
  }
  if(image) at_arrayu8_destroy(&image);
}

int main(int argc, char* argv[]){
  GtkApplication* app = gtk_application_new("io.github.atkv",G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app),argc, argv);
  g_object_unref(app);
  return status;
}
