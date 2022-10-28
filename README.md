# BBCodeParser

A simple BBCode parser made in C++.

<img src="https://i.imgur.com/RUB3u9d.png" alt="BBCodeParser in action" width="55%" />

Currently handles just the tags themselves and renders them according to their "name" (the first parameter inside a square bracket tag), and their "inner content".

For example, the following BBCode:

```
[b]
[u]
I'm alive!
test
[b]Another bold[/b]
[img]pic.png[/img]
[u]
[/b]
```

Can be converted to:

``` html
<b>
<u>
I'm alive!
test
<b>another bold</b>
<img src="pic.png" alt="" />
</u>
</b>

```

`

## To-do list

- [ ] Add proper parameter parsing and allow accessing them while rendering a tag
- [ ] Add a data-structure description to the README.md file
- [ ] Define rendering on erratic behavior
- [ ] Make certain aspects of the code more elegant and organized (i.e. file structure, data regarding available tags, etc.)
- [ ] Use Streams/Buffers to allow pipeling
