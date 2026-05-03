#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("iter/task_file")
int dump_open_files(struct bpf_iter__task_file *ctx) {
    struct task_struct *task = ctx->task;
    struct file *file = ctx->file;
    __u32 fd = ctx->fd;

    // Якщо це кінець ітерації, ядро передає NULL
    if (task == NULL || file == NULL) {
        return 0;
    }

    // Просто виводимо PID процесу та дескриптор файлу
    BPF_SEQ_PRINTF(ctx->meta->seq, "PID: %-6d | FD: %-4d\n", task->tgid, fd);

    return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
