## Introduction

Hi everyone, I've decided to provide you with a small status update. I've been
working for a few months to create this app that I hope will liberate humanity.
Seriously, at the very least I hope it will liberate you from being forced
to observe data only in the format that is of most convenience to their
creator.

## Progress

In August I finally decided to implement what has been in my mind for at least
a couple years: data transformation platform for regular consumers (i.e. not
profit-hungry corporations). User friendly, mobile, desktop, powerful yet
accessible. Able to process RSS feeds, wiki pages, online bank transaction,
and other datasets that regular consumers can and do depend on.

At first I thought it would be good to make it web-based, so that people could
share the URL to their data with their friends. However, due to privacy
concerns, I decided, for now, to not use my erlang server, and instead focus
development on the Qt mobile/desktop app.

So far, it allows the user to specify regular expressions (text/HTML), but not
path expressions (XML/JSON). After that is done, work will begin on charts, and
possibly maps. I'm not sure if there is a way users could program the regexes
interactively.
