# Start compiler for ubuntu base
FROM ubuntu AS compiler

# Create and move to 42_minishell directory
WORKDIR /42_minishell

# Copy source files 
COPY ./srcs ./srcs
COPY ./inc ./inc
COPY ./lib ./lib
COPY Makefile Makefile

# Copy tester
COPY ./tester ./tester

# Install build tools and dependencies
RUN apt-get update
RUN apt-get -y install libreadline-dev=8.1.2-1 build-essential dos2unix

# Start building
RUN make

# Make file compatible with Linux
RUN dos2unix tester/tester.sh
RUN dos2unix tester/minitest.csv

# Start another Docker
FROM ubuntu

# Install only dependencies
RUN apt-get update
RUN apt-get -y install libreadline-dev=8.1.2-1

# Copy built binary and tester from compiler
COPY --from=compiler /42_minishell/minishell /minishell
COPY --from=compiler /42_minishell/tester /tester

# Move into tester folder
WORKDIR /tester

# Start tester
CMD [ "bash", "./tester.sh" ]