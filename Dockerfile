# Start your image with a node base image
FROM ubuntu AS compiler

# The /app directory should act as the main application directory
WORKDIR /42_minishell

# Copy local directories to the current local directory of our docker image (/app)
COPY ./srcs ./srcs
COPY ./inc ./inc
COPY ./lib ./lib
COPY ./tester ./tester
COPY Makefile Makefile

# Install node packages, install serve, build the app, and remove dependencies at the end
RUN apt-get update
RUN apt-get -y install libreadline-dev=8.1.2-1 build-essential dos2unix
RUN make
RUN dos2unix tester/tester.sh
RUN dos2unix tester/minitest.csv

# Start the app using serve command
FROM ubuntu

RUN apt-get update
RUN apt-get -y install libreadline-dev=8.1.2-1

COPY --from=compiler /42_minishell/minishell /minishell
COPY --from=compiler /42_minishell/tester /tester

WORKDIR /tester

CMD [ "bash", "./tester.sh" ]