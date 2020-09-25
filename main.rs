use cursive::event::{Event, Key};
use cursive::views::{Dialog, TextView, LinearLayout, EditView, OnEventView, TextArea};
use cursive::traits::*;
use cursive::Cursive;
use cursive::menu::MenuTree;
// use cursive::theme::{BaseColor, Color, Effect, Style, ColorStyle};
// use cursive::utils::markup::StyledString;

// This example define a custom view that prints any event it receives.
// This is a handy way to check the input received by cursive.
//add a

fn main() {
    let mut siv = cursive::default();

    siv.menubar()
        .add_subtree(
            "Edit",
            MenuTree::new()
                    .leaf("name", move |s|{
                        s.menubar().find_subtree("Edit").unwrap();
                    })
        )
        .add_subtree(
            "Help",
            MenuTree::new()
                    .leaf("About", |s| {
                        s.add_layer(Dialog::info("created by a anon pajeet"))
                    })
        )
        .add_delimiter()
        .add_leaf("Quit", |s| s.quit());

    siv.add_layer( Dialog::new()
                .title("gib name")
                .content(
                    EditView::new()
                        .on_submit(racing_screen)
                        .with_name("username")
                )
                .button("Ok",|s| {
                    let name = s.call_on_name("username", |view: &mut EditView| {
                        view.get_content() //get the input
                    })
                    .unwrap();
                    racing_screen(s, &name);
                }),
    );
    // siv.add_layer(Dialog::text("again"));

    siv.add_global_callback(Key::Esc, |s| s.select_menubar());
    // siv.select_menubar();

    // siv.set_autohide_menu(false);

    siv.run();
}

fn racing_screen(s: &mut Cursive, name: &str)
{
    if name.is_empty()
    {
        s.add_layer(Dialog::info("You forgot gib name"));
    } else {
        //todo fetch content from api or database
        let content = "just as I'm giving up, my heart is palpitating. Here comes another one, it's so intoxicating. And being where I've been, I know that in the end I'll do it all again.";
        // let alignment = VAlign.get_offset();

        let racing_text = Dialog::around(
                        TextView::new(content)
                        .with_name("edittext")
                        .fixed_height(10),
        );

        let input_text = Dialog::around(
                        TextArea::new()
                        .with_name("text")
                        .fixed_height(5),
        );
    
        let second_racing_text = Dialog::around(
            TextView::new(name),
        );
    

        // s.set_autorefresh(false);
        s.pop_layer();

        // let mut count = 0;
        s.add_layer( OnEventView::new(Dialog::around(LinearLayout::vertical()
                .child(racing_text)
                // .child(input_text)
                .child(second_racing_text)
        // )).on_event(Event::Char(content.chars().nth(0).unwrap()), move |s| racing(s)));
           )).on_event(Key::Enter, |s| racing(s)));

    }
}

fn racing(siv: &mut Cursive) {
    // let mut count : usize = 0;
    siv.screen_mut().call_on_name("edittext", |view: &mut TextView|{
        let content = text_color(view.get_content().source());
        view.set_content(content);
    });
}

fn text_color(text: &str) -> String {
    text.chars().rev().collect()
}
