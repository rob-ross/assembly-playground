
## 1. Headings

Headings use the hash symbol (#) followed by a mandatory space. 
There are 6 levels corresponding to HTML tags `<h1>` through `<h6>`.
# Heading 1
## Heading 2
### Heading 3
#### Heading 4
##### Heading 5
###### Heading 6

## 2. Text Emphasis
You can apply italic, bold, or strikethrough styling using asterisks (*), underscores (_), or tildes (~).

| Style | Syntax | Example |
|:-----| :--- | :--- |
| Italic        |	Wrap text in * or _     |	*Italic text* or _Italic text_ |
| Bold          |	Wrap text in ** or __   |	**Bold text** or __Bold text__ |
| Bold & Italic |	Wrap text in *** or ___ |	***Bold and italic***          |
| Strikethrough |	Wrap text in ~~         |	~~Strikethrough text~~         |

## 3. Lists
Markdown handles both ordered (numbered) and unordered (bulleted) lists.

### Unordered Lists
Precede items with a minus (-), asterisk (*), or plus (+) followed by a space. Indent by 4 spaces or 1 tab to create nested sub-items.
- Item 1
- Item 2
    - Sub-item 2a
    - Sub-item 2b

### Ordered Lists
Precede items with a number followed by a period and a space. The exact numbers do not need to be sequential; the markdown parser handles numbering automatically.
1. First item
1. Second item
1. Third item

### Task Lists
Commonly supported in extended variants like GitHub Flavored Markdown (GFM). Use a list marker followed by [ ] for unchecked items or [x] for checked items.
- [x] Completed task
- [ ] Incomplete task

## 4. Links and Images
Links and images share a very similar structural pattern.

### Links
Wrap the anchor text in square brackets and the URL in parentheses.
[Visit OpenAI](https://openai.com)

### Images
Use the exact same structure as a link but prefix it with an exclamation mark (!). The text inside the brackets acts as the alt text.
![Logo Description](https://example.com)


## 5. Code blocks
You can present code inline or inside a dedicated multi-line block.

### Inline Code
Wrap small snippets or variables inside \``single backticks`\`.
### Fenced Code Blocks
Wrap multi-line code inside triple backticks (```) on separate lines. You can optionally append the language name right after the first set of backticks to trigger syntax highlighting.
```python
def say_hello():
    print("Hello, World!")
```


## 6. Blockquotes
Prefix your paragraphs with a greater-than sign (>) and a space. You can nest quotes by adding multiple characters (>>).
> This is a single-level blockquote.
>> This is a nested blockquote response.
>>> Third!

## 7. Tables
Tables are part of extended syntax. Use pipes (|) to separate columns and hyphens (-) to define headers. Use colons (:) within the hyphen row to set text alignment.

| Left Aligned | Centered | Right Aligned |
| :--- | :---: | ---: |
| Data 1 | Data 2 | Data 3 |
| Data 4 | Data 5 | Data 6 |

## 8. Miscellaneous Syntax
### Horizontal Rules

Create a clean dividing line by typing three or more hyphens (---), asterisks (***), or underscores (___) on an empty line.

---

### Escaping Characters

If you want literal formatting characters (like an actual asterisk or hash symbol) to print onto the screen instead of altering the text structure, prefix them with a backslash \\.
Example: \*This will not be italicized\*.

### Line Breaks
Continuous lines are wrapped to fit the display area. 
White space at the beginning and end of lines is removed (but more than 3 spaces at the start of the line create a block.)
A single line break (i.e. 'enter' key) is ignored and the line is considered continuous. Two 'enters' create a paragraph, 
so the next line will start with an empty line before it. To place text on the next line without creating a new paragraph, 
enter two spaces and 'enter':
This is the first line.  [Space][Space][Enter]  
This starts directly on the next line without empty padding.   

You can also use the `<br>` html tag to force a line break.<br>
Example:<br>
This is line one.`<br>`<br>
This is line two.


## 9. Obsidian Syntax

### Wikilinks
Double brackets:	[[Note Name]]

### Embeds
Exclamation + brackets: ![[Note Name]] or ![[image.png]]

### Highlights
Use double equals '\==':
==highlighted text==

### Callouts
Blockquote tags: > [!note] Title


### Block References	

Caret ID: ^block-id

### LaTeX Math & Comments
Requires MathJax / Percent plugin. Example: $math$ or %%comment%%
