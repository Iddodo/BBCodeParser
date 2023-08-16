# BBCodeParser
This project is currently undergoing a serious rewrite,
adding multiple features which were unexisting before and imporving safety and readability.

A working prototype will be uploaded in the following days.


## TODO
- [ ] Create the parameter list during the tag definition phase using a temporary BBCodeTag object
- [ ] Create either a BBCodeNestableTag or a BBCodeSelfClosingTag according to the final state
- [ ] Add two new classes that will inherit from BBCodeTag: BBCodeNestableTag and BBCodeSelfClosing tag.
- [ ] Add constructors that would enable us to initialize from an existing BBCodeTag object.
- [ ] Finally, edit the existing BBCodeRenderer class and its descendants to accommodate for this change.
