FROM gcc:10

WORKDIR /app

COPY . .

RUN make CFLAGS="-std=c89 -Wall -Wextra -pedantic"

CMD ["./tester"]
