#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/inotify.h>
#include <sys/epoll.h>

int main(int argc, char *argv[]) {
	int inotify_fd = inotify_init1(IN_CLOEXEC);
	if (inotify_fd == -1) {
		perror("inotify_init");
		return EXIT_FAILURE;
	}

	int watch_fd = inotify_add_watch(inotify_fd, argv[1], IN_CLOSE_WRITE);
	if (watch_fd == -1) {
		perror("inotify_add_watch");
		return EXIT_FAILURE;
	}

	const int name_max = 32;
	char buf[sizeof(struct inotify_event) + name_max + 1];

	for (;;) {
		int bytes_read = read(inotify_fd, buf, sizeof(buf));
		if (bytes_read == 0) {
			perror("read 0 bytes");
			return EXIT_FAILURE;
		}
		if (bytes_read == -1) {
			perror("read");
			return EXIT_FAILURE;
		}

		struct inotify_event *ev = (struct inotify_event *)buf;
		if (ev->mask & IN_IGNORED) {
			printf("file was removed from inotify!\n");
		} else {
			printf("Events: %x\n", ev->mask);
			printf("Name: %s\n", ev->name);
		}
	}

	//	int epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	//	if (epoll_fd == -1) {
	//		perror("epoll_create");
	//		return EXIT_FAILURE;
	//	}
	//
	//	struct epoll_event ev;
	//	ev.events = EPOLLIN;
	//	ev.data.fd = inotify_fd;
	//
	//	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, inotify_fd, &ev) == -1) {
	//		perror("epoll_ctl");
	//		return EXIT_FAILURE;
	//	}
	//
	//	printf("Watching %s\n", argv[1]);
	//
	//	struct epoll_event events[10];
	//
	//	for (;;) {
	//		int nfds = epoll_wait(epoll_fd, events, 10, -1);
	//		if (nfds == -1) {
	//			perror("epoll_ctl");
	//			return EXIT_FAILURE;
	//		}
	//		printf("%d events\n", nfds);
	////		int i;
	////		for (i = 0; i < nfds; i++) {
	////			printf("%s was modified\n", argv[1]);
	////		}
	//	}
	//


	close(watch_fd);
	close(inotify_fd);
}
