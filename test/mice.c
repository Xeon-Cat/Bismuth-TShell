#include <libinput.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// 自定义结构维护鼠标位置
struct MouseState {
    double x;
    double y;
};

// 静态函数用于设备打开
static int open_restricted(const char *path, int flags, void *user_data) {
    return open(path, flags);
}

// 静态函数用于设备关闭
static void close_restricted(int fd, void *user_data) {
    close(fd);
}

// libinput接口定义
static const struct libinput_interface interface = {
        .open_restricted = open_restricted,
        .close_restricted = close_restricted,
};

int main() {
    struct libinput *li;
    struct libinput_event *event;
    struct MouseState mouse = {0.0, 0.0};

    // 初始化 libinput 上下文
    li = libinput_path_create_context(&interface, NULL);

    // 监控所有输入设备（需要根据实际设备路径修改）
    libinput_path_add_device(li, "/dev/input/event0");

    // 事件循环
    while ((event = libinput_get_event(li)) != NULL) {
        enum libinput_event_type type = libinput_event_get_type(event);

        if (type == LIBINPUT_EVENT_POINTER_MOTION) {
            struct libinput_event_pointer *p_event = libinput_event_get_pointer_event(event);
            double dx = libinput_event_pointer_get_dx(p_event);
            double dy = libinput_event_pointer_get_dy(p_event);

            // 更新鼠标位置
            mouse.x += dx;
            mouse.y += dy;

            printf("Current position: (%.2f, %.2f)\n", mouse.x, mouse.y);
        }

        libinput_event_destroy(event);
        libinput_dispatch(li);
    }

    // 清理资源
    libinput_unref(li);
    return 0;
}