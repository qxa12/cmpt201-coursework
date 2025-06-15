#include <stdint.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void print_str(const char *s) {
  size_t len = 0;
  while (s[len])
    len++;
  write(STDOUT_FILENO, s, len);
}

void print_byte(unsigned char byte) {
  char c;
  if (byte == 0)
    c = '0';
  else if (byte == 1)
    c = '1';
  else
    c = '?';
  write(STDOUT_FILENO, &c, 1);
  write(STDOUT_FILENO, "\n", 1);
}

void print_hex_digit(uint64_t digit) {
  char c = "0123456789abcdef"[digit & 0xF];
  write(STDOUT_FILENO, &c, 1);
}

void print_ptr(void *ptr) {
  if (!ptr) {
    print_str("(nil)");
    return;
  }

  uintptr_t addr = (uintptr_t)ptr;
  print_str("0x");
  int started = 0;

  for (int shift = 60; shift >= 0; shift -= 4) {
    uint64_t nibble = (addr >> shift) & 0xF;
    if (nibble || started || shift == 0) {
      print_hex_digit(nibble);
      started = 1;
    }
  }
}

void print_uint64(uint64_t num) {
  char buf[21];
  int i = 0;

  if (num == 0) {
    buf[i++] = '0';
  } else {
    while (num > 0) {
      buf[i++] = '0' + (num % 10);
      num /= 10;
    }
  }

  for (int j = i - 1; j >= 0; j--) {
    write(STDOUT_FILENO, &buf[j], 1);
  }
}

int main() {
  void *start = sbrk(256);
  struct header *block1 = (struct header *)start;
  struct header *block2 = (struct header *)((char *)start + 128);

  block1->size = 128;
  block1->next = NULL;
  block2->size = 128;
  block2->next = block1;

  memset(block1 + 1, 0, 128 - sizeof(struct header));
  memset(block2 + 1, 1, 128 - sizeof(struct header));

  print_str("first block: ");
  print_ptr(block1);
  print_str("\nsecond block: ");
  print_ptr(block2);
  print_str("\nfirst block size: ");
  print_uint64(block1->size);
  print_str("\nfirst block next: ");
  print_ptr(block1->next);
  print_str("\nsecond block size: ");
  print_uint64(block2->size);
  print_str("\nsecond block next: ");
  print_ptr(block2->next);
  print_str("\n");

  for (size_t i = 0; i < 128 - sizeof(struct header); i++) {
    unsigned char *data = (unsigned char *)(block1 + 1);
    print_byte(data[i]);
  }

  for (size_t i = 0; i < 128 - sizeof(struct header); i++) {
    unsigned char *data = (unsigned char *)(block2 + 1);
    print_byte(data[i]);
  }

  return 0;
}
