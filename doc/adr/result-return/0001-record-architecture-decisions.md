# 1. Record architecture decisions

Date: 2021-11-21

## Status

Accepted

## Context

We need to create modern and domain oriented result type to descrbe domains failures.
Indeed:

- Domain failures and code errors are not really the same issues.
- We need to have infrastructure logger and code.
- We need to catch the problem of having domain failures with rich expressivity without using exception.

## Decision

Create Result class that is a specialization of a monade to describe success and failures.
This class will contains a gobal logger.
This class should be build time as possible using meta programation.

## Consequences

We need to use `Result<Sucess, Failures...>` as return type of domain functions if the method can fail.
