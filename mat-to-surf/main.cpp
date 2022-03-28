#include "gst/gst.h"

#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <atomic>
#include <thread>

static std::atomic<bool> running(true);

void interruptHandler(int) {
    running.store(false);
}

void start_pipeline(GMainContext* context, GMainLoop* loop, GstElement* pipeline) {
    g_main_context_push_thread_default(context);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_main_loop_run(loop);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = interruptHandler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    gst_init(nullptr, nullptr);
    GstRegistry* registry = gst_registry_get();
    gst_registry_scan_path(registry, ".");

    std::ifstream file("pipeline.txt");
    std::string content;
    getline(file, content);
    GstElement* pipeline = gst_parse_launch(content.c_str(), nullptr);

    GMainContext* context = g_main_context_new();
    GMainLoop* loop = g_main_loop_new(context, false);
    std::thread thread(start_pipeline, context, loop, pipeline);

    while (running.load()) {}

    gst_element_set_state(pipeline, GST_STATE_NULL);
    g_main_loop_quit(loop);
    thread.join();

    gst_object_unref(pipeline);
    printf("done\n");
}