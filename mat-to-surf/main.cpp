#include "gst/gst.h"

#include <fstream>

int main() {
    gst_init(nullptr, nullptr);
    GstRegistry* registry = gst_registry_get();
    gst_registry_scan_path(registry, "mat-to-surf/gst");

    std::ifstream file("mat-to-surf/pipeline.txt");
    std::string content;
    getline(file, content);
    GstElement* pipeline = gst_parse_launch(content.c_str(), nullptr);

    GMainContext* context = g_main_context_new();
    GMainLoop* loop = g_main_loop_new(context, false);
    g_main_context_push_thread_default(context);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_main_loop_run(loop);

    gst_element_set_state(pipeline, GST_STATE_NULL);
    g_main_loop_quit(loop);
    gst_object_unref(pipeline);
}